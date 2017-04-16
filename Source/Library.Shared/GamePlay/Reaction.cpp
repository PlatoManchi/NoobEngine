#include "pch.h"
#include "Reaction.h"
#include "GamePlay/World.h"
#include "GamePlay/Sector.h"
#include "GamePlay/Entity.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(Reaction)

		const std::string Reaction::sReactionKey = "reaction";

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
			pPublisher;
		}

		void Reaction::Populate()
		{
			ActionList::Populate();
		}

		void Reaction::SetParent(Attribute* pParent)
		{
			assert(pParent->Is(World::TypeIdClass()) || pParent->Is(Sector::TypeIdClass()) || pParent->Is(Entity::TypeIdClass()) || pParent->Is(ActionList::TypeIdClass()));

			if (mParent != pParent)
			{
				pParent->Adopt(*this, sReactionKey);
				mParent = pParent;
			}
		}
	}
}