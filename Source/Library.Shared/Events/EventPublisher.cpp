#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"

namespace NoobEngine
{
	namespace Events
	{
		RTTI_DEFINITIONS(EventPublisher)

		EventPublisher::EventPublisher(Container::Vector<std::shared_ptr<EventSubscriber>>& pSubscribers, std::mutex& pMutex) :
			mSubscriberList(&pSubscribers), mMutex(&pMutex), mIsExpired(false)
		{
		}


		EventPublisher::EventPublisher(EventPublisher& pOther) : 
			mSubscriberList(pOther.mSubscriberList), mIsExpired(pOther.mIsExpired), mMutex(pOther.mMutex)
		{
		}

		EventPublisher& EventPublisher::operator=(EventPublisher& pOther)
		{
			if (this != &pOther)
			{
				mSubscriberList = pOther.mSubscriberList;
				mIsExpired = pOther.mIsExpired;
				mMutex = pOther.mMutex;
			}
			return *this;
		}

		EventPublisher::EventPublisher(EventPublisher&& pOther) :
			RTTI(std::move(pOther)), mSubscriberList(pOther.mSubscriberList), mIsExpired(pOther.mIsExpired), mMutex(pOther.mMutex)
		{
			pOther.mSubscriberList = nullptr;
			pOther.mMutex = nullptr;
		}

		EventPublisher& EventPublisher::operator=(EventPublisher&& pOther)
		{
			if (this != &pOther)
			{
				mSubscriberList = pOther.mSubscriberList;
				mIsExpired = pOther.mIsExpired;
				mMutex = pOther.mMutex;

				pOther.mSubscriberList = nullptr;
				pOther.mMutex = nullptr;
			}
			return *this;
		}

		bool EventPublisher::IsExpired() const
		{
			return mIsExpired;
		}

		void EventPublisher::Deliver()
		{
			if (!mSubscriberList)
			{
				throw std::exception("Invalid publisher.");
			}

			mIsExpired = true;

			Container::Vector<std::shared_ptr<EventSubscriber>> tmpSubscriberList;
			{
				// empty block created to lock_guard the mSubscriberList
				std::lock_guard<std::mutex> lock(*mMutex);
				tmpSubscriberList = *mSubscriberList;
			}

			std::vector<std::future<void>> futureList;

			for (std::shared_ptr<EventSubscriber> subscriber : tmpSubscriberList)
			{
				// invoking notify asynchronously
				futureList.emplace_back(std::async([&]() {
					subscriber->Notify(*this);
				}));
			}

			// block until all threads execution are complete
			for (std::future<void>& fut : futureList)
			{
				// TODO : exception aggregation
				fut.get();
			}

			tmpSubscriberList.Clear();
			futureList.clear();
		}
	}
}