#include "pch.h"
#include "Reaction.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(Reaction)

		Reaction::Reaction() :
			ActionList()
		{
			Populate();
		}

		void Reaction::Update(WorldState& pWorldState)
		{
			ActionList::Update(pWorldState);
		}

		void Reaction::Notify(Events::EventPublisher& pPublisher)
		{
			EventSubscriber::Notify(pPublisher);
		}

		void Reaction::Populate()
		{
			ActionList::Populate();
		}
	}
}