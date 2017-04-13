#include "pch.h"
#include "EventQueue.h"

namespace NoobEngine
{
	namespace Events
	{
		RTTI_DEFINITIONS(EventQueue)

		EventQueue::EventQueue() :
			mPublisherList(), mGarbagePublisherList()
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
			
			// loop through all events and check if they expired. if they do then notify the subscribers
			for (Publisher publisher : mPublisherList)
			{
				if (publisher.mEnqueuedTime + publisher.mDelay >= currentTime)
				{
					publisher.mPublisher->Deliver();
					mGarbagePublisherList.PushBack(publisher);
				}
			}

			// deleting all the events that expired
			for (Publisher publisher : mGarbagePublisherList)
			{
				mPublisherList.Remove(publisher);
			}
			mGarbagePublisherList.Clear();
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