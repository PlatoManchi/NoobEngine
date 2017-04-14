#pragma once

#include "Events/EventSubscriber.h"

namespace SupportingClasses
{
	class EventMessageOne : public NoobEngine::Events::EventSubscriber
	{
	public:
		int32_t mNotifiedCount;

		EventMessageOne() : mNotifiedCount(0)
		{

		}

		void Notify(NoobEngine::Events::EventPublisher& pPublisher) override
		{
			pPublisher;
			++mNotifiedCount;
		}

		void Reset()
		{
			mNotifiedCount = 0;
		}
	};

}