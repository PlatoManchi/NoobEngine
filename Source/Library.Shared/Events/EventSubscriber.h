#pragma once
#include "Runtime/RTTI.h"
#include "EventPublisher.h"

namespace NoobEngine
{
	namespace Events
	{
		/**
			Any class that wants to subscribe to events has to extend this interface.
		*/
		class EventSubscriber abstract : public Runtime::RTTI
		{
			RTTI_DECLARATIONS(EventSubscriber, RTTI)

		public:
			/**
				@brief This will be called when ever the event is fired.
				@param[in] pEventPublisher Reference to EventPublisher that fired this event.
			*/
			virtual void Notify(EventPublisher& pPublisher) = 0;
		};
	}
}