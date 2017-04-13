#include "pch.h"
#include "EventQueue.h"

namespace NoobEngine
{
	namespace Events
	{
		RTTI_DEFINITIONS(EventQueue)

		EventQueue::EventQueue() :
			mPublisherList()
		{
		}

		void EventQueue::Enqueue(std::shared_ptr<EventPublisher> pEventPublisher, const GamePlay::GameTime& pGameTime, float pDelay /* = 0.0f */)
		{
			Publisher tmpPublisher;
			tmpPublisher.mPublisher = pEventPublisher;
			tmpPublisher.mEnqueuedTime = pGameTime.CurrentTime();
			tmpPublisher.mDelay = std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(pDelay * 1000.0f));

			mPublisherList.PushBack(tmpPublisher);
		}

		
		void EventQueue::Send(std::shared_ptr<EventPublisher> pEventPublisher)
		{
			pEventPublisher->Deliver();
		}

		void EventQueue::Update(const GamePlay::GameTime& pGameTime)
		{
			const std::chrono::high_resolution_clock::time_point& currentTime = pGameTime.CurrentTime();
			
			uint32_t numOfExpiredEvents = 0U;
			// loop through all events and check if they expired. if they do then notify the subscribers
			for (uint32_t i = 0; i < mPublisherList.Size() - numOfExpiredEvents; ++i)
			{
				Publisher& publisher = mPublisherList[i];

				// check if the event should be notified
				if (publisher.mEnqueuedTime + publisher.mDelay >= currentTime)
				{
					// notify subscribers only if the event is not expired
					if (!publisher.mPublisher->IsExpired())
					{
						publisher.mPublisher->Deliver();
					}
					
					numOfExpiredEvents++;

					// swap the expired event to end of the vector
					Publisher& tmp = mPublisherList[mPublisherList.Size() - numOfExpiredEvents];
					mPublisherList[mPublisherList.Size() - numOfExpiredEvents] = mPublisherList[i];
					mPublisherList[i] = tmp;
					
					// decrement i so that the swapped event is also checked for expiration
					--i;
				}
			}

			// bulk remove all the events that expired at once
			Container::Vector<Publisher>::Iterator garbageBeginItr(&mPublisherList, mPublisherList.Size() - numOfExpiredEvents);
			mPublisherList.Remove(garbageBeginItr, mPublisherList.end());
		}

		void EventQueue::Clear()
		{
			mPublisherList.Clear();
		}

		bool EventQueue::IsEmpty()
		{
			return mPublisherList.Size() == 0;
		}

		uint32_t EventQueue::Size()
		{
			return mPublisherList.Size();
		}
	}
}