#pragma once

#include "Events/EventSubscriber.h"
#include "Events/EventQueue.h"
#include "Events/Event.h"
#include "GamePlay/GameTime.h"

namespace SupportingClasses
{
	class EnqueueEventSubscriber : public NoobEngine::Events::EventSubscriber
	{
	public:
		
		EnqueueEventSubscriber(NoobEngine::GamePlay::GameTime* pGameTime);

		void Notify(NoobEngine::Events::EventPublisher& pPublisher) override;

		NoobEngine::GamePlay::GameTime* mGameTime;
	};

}