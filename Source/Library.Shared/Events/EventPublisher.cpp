#include "pch.h"
#include "EventPublisher.h"

namespace NoobEngine
{
	namespace Events
	{
		RTTI_DEFINITIONS(EventPublisher)

		EventPublisher::EventPublisher(const Container::Vector<std::shared_ptr<EventSubscriber>>& pSubscribers) :
			mSubscriberList(pSubscribers), mIsExpired(false)
		{
		}


		EventPublisher::EventPublisher(EventPublisher& pOther)
		{
			mSubscriberList = pOther.mSubscriberList;
			mIsExpired = pOther.mIsExpired;
		}

		EventPublisher& EventPublisher::operator=(EventPublisher& pOther)
		{
			if (this != &pOther)
			{
				mSubscriberList = pOther.mSubscriberList;
				mIsExpired = pOther.mIsExpired;
			}
			return *this;
		}

		EventPublisher::EventPublisher(EventPublisher&& pOther) :
			RTTI(std::move(pOther))
		{
			mSubscriberList = std::move(pOther.mSubscriberList);
			mIsExpired = pOther.mIsExpired;
		}

		EventPublisher& EventPublisher::operator=(EventPublisher&& pOther)
		{
			if (this != &pOther)
			{
				mSubscriberList = std::move(pOther.mSubscriberList);
				mIsExpired = pOther.mIsExpired;
			}
			return *this;
		}

		bool EventPublisher::IsExpired() const
		{
			return mIsExpired;
		}

		void EventPublisher::Deliver()
		{
			mIsExpired = true;
			for (std::shared_ptr<EventSubscriber> subscriber : mSubscriberList)
			{
				subscriber->Notify();
			}
		}
	}
}