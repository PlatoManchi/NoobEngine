#pragma once

#include "Runtime/RTTI.h"
#include "GamePlay/GameTime.h"
#include "Container/Vector.h"
//#include "EventSubscriber.h"


namespace NoobEngine
{
	namespace Events
	{
		class EventSubscriber;

		class EventPublisher abstract : public Runtime::RTTI
		{
			RTTI_DECLARATIONS(EventPublisher, RTTI)

		public:
			/**
				@brief Default constructor
			*/
			EventPublisher(Container::Vector<std::shared_ptr<EventSubscriber>>& pSubscribers);

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
			/**
				Pointer to vector that contains all the subscribers for this Publisher
				Since this is a static vector from Event class, saving it as pointer is better than reference
				because the move semantics can get problematic with reference.
			*/
			Container::Vector<std::shared_ptr<EventSubscriber>>* mSubscriberList;

			/**
				Is event expired.
			*/
			bool mIsExpired;
		};
	}
}