#include "pch.h"
#include "Entity.h"
#include "Sector.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(GamePlay::Entity)

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

		Sector & Entity::GetParentSector() const
		{
			return *mParent;
		}

		void Entity::SetParentSector(Sector& pSector)
		{
			if (mParent != &pSector)
			{
				pSector.Adopt(*this, Sector::sEntitiesKey);
			}
		}

		void Entity::Update(WorldState& pGameState)
		{
			pGameState;
		}
	}
}