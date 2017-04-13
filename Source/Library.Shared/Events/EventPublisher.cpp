#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"

namespace NoobEngine
{
	namespace Events
	{
		RTTI_DEFINITIONS(EventPublisher)

		EventPublisher::EventPublisher(Container::Vector<std::shared_ptr<EventSubscriber>>& pSubscribers) :
			mSubscriberList(&pSubscribers), mIsExpired(false)
		{
		}


		EventPublisher::EventPublisher(EventPublisher& pOther) : 
			mSubscriberList(pOther.mSubscriberList), mIsExpired(pOther.mIsExpired)
		{
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
			RTTI(std::move(pOther)), mSubscriberList(pOther.mSubscriberList), mIsExpired(pOther.mIsExpired)
		{
			pOther.mSubscriberList = nullptr;
		}

		EventPublisher& EventPublisher::operator=(EventPublisher&& pOther)
		{
			if (this != &pOther)
			{
				mSubscriberList = pOther.mSubscriberList;
				mIsExpired = pOther.mIsExpired;

				pOther.mSubscriberList = nullptr;
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
			for (std::shared_ptr<EventSubscriber> subscriber : *mSubscriberList)
			{
				subscriber->Notify(*this);
			}
		}
	}
}