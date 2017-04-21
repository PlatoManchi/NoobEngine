#pragma once
#include "Runtime/RTTI.h"
#include "EventSubscriber.h"
#include "Container/Vector.h"
#include "EventPublisher.h"

namespace NoobEngine
{
	namespace Events
	{
		template <typename  T>
		class Event : public EventPublisher
		{
			RTTI_DECLARATIONS(Event, EventPublisher)

		public:
			/**
				@brief Constructor
				@param[in] pPayload The message that needs to be delivered
				param[in] pShouldDeletePostPublishing Should the event be deleted after publishing the event.
			*/
			Event(T& pPayload);

			/**
				@brief Copy constructor
				@param[in] pOther The other event that needs to be copied.
			*/
			Event(Event& pOther);

			/**
				@brief Overloading = operator
				@param[in] pOther The other event that this event needs to be assigned to.
			*/
			Event& operator=(Event& pOther);

			/**
				@brief Move constructor
				@param[in] pOther The other event from which data should be stolen.
			*/
			Event(Event&& pOther);

			/**
				@brief Overloaded move = operator
				@param[in] pOther The other event from which data should be stolen.
			*/
			Event& operator=(Event&& pOther);

			/**
				@brief Subscribe the subscriber to this event.
				@param[in] pSubscriber The subscriber that is subscribing for this event.
			*/
			static void Subscribe(std::shared_ptr<EventSubscriber> pSubscriber);

			/**
				@brief Unsubscribe the subscriber form this event.
				@param[in] pSubscriber The subscriber to unsubscribe from this event.
			*/
			static void Unsubscribe(std::shared_ptr<EventSubscriber> pSubscriber);

			/**
				@brief Unsubscribe all subscribers from event of this type.
			*/
			static void UnsubscribeAll();

			/**
				@brief Returns the message that this event is storing.
				@return Reference to the message that this event is storing.
			*/
			const T& Message() const;

		private:
			T mPayload;
			/**
				Static list of subscribers to event of template type T
			*/
			static Container::Vector<std::shared_ptr<EventSubscriber>> sSubscriberList;

			/**
				Static mutex that is used to make the event of template type T thread safe.
			*/
			static std::mutex sMutex;
		};
	}
}

#include "Event.inl"