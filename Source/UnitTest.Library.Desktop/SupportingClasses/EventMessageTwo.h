#pragma once
#include "Events/EventSubscriber.h"

namespace SupportingClasses
{
	class EventMessageTwo : public NoobEngine::Events::EventSubscriber
	{
		RTTI_DECLARATIONS(EventMessageTwo, NoobEngine::Events::EventSubscriber)

	public:
		bool mIsNotified;

		EventMessageTwo() : mIsNotified(false)
		{

		}

		void Notify(NoobEngine::Events::EventPublisher& pPublisher) override
		{
			pPublisher;
			mIsNotified = true;
		}

		void Reset()
		{
			mIsNotified = false;
		}
	};

	RTTI_DEFINITIONS(EventMessageTwo)
}