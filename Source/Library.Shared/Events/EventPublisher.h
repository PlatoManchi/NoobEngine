#pragma once

#include "Runtime/RTTI.h"
#include "GamePlay/GameTime.h"
#include "Container/Vector.h"
#include "EventSubscriber.h"

namespace NoobEngine
{
	namespace Events
	{
		class EventPublisher abstract : public Runtime::RTTI
		{
			RTTI_DECLARATIONS(EventPublisher, RTTI)

		public:
			/**
				@brief Default constructor
			*/
			EventPublisher(const Container::Vector<std::shared_ptr<EventSubscriber>>& pSubscribers);

			/**
				@brief Default Copy constructor
			*/
			EventPublisher(EventPublisher& pOther);
			/**
				@brief Overloading = operator
			*/
			EventPublisher& operator=(EventPublisher& pOther);
			/**
				@brief Move constructor
			*/
			EventPublisher(EventPublisher&& pOther);
			/**
				@brief Move = operator
			*/
			EventPublisher& operator=(EventPublisher&& pOther);

			/**
				@brief returns true if the event expired else false;
			*/
			bool IsExpired() const;

			/**
				@brief Call notify on all the subscribers.
			*/
			void Deliver();
		private:
			Container::Vector<std::shared_ptr<EventSubscriber>> mSubscriberList;
			bool mIsExpired;
		};
	}
}