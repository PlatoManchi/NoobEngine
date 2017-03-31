#include "pch.h"
#include "Entity.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		Entity::Entity() :
			Attribute()
		{
		}

		Entity::~Entity()
		{
		}

		std::string Entity::Name() const
		{
			return mName;
		}

		void Entity::SetName(const std::string& pName)
		{
			mName = pName;
		}

		Sector & Entity::GetSector() const
		{
			return *mParent;
		}

		void Entity::SetSector(const Sector& pSector)
		{
			if (mParent != &pSector)
			{
				// TODO: Adopt this entity into pSector
			}
		}

		void Entity::Update(WorldState& pGameState)
		{
			pGameState;
		}


	}
}