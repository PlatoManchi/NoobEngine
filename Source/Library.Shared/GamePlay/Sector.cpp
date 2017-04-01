#include "pch.h"
#include "Sector.h"
#include "World.h"
#include "Entity.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(GamePlay::Sector)

		const char* Sector::sEntitiesKey = "Entities";

		Sector::Sector() :
			Attribute()
		{
		}

		Sector::~Sector()
		{
		}

		std::string Sector::Name() const
		{
			return mName;
		}

		void Sector::SetName(const std::string& pName)
		{
			mName = pName;
		}

		Runtime::Datum& Sector::Entities()
		{
			return Append(sEntitiesKey);
		}

		Entity& Sector::CreateEntity(const std::string& pEntityType, const std::string& pEntityName)
		{
			Entity* newEntity = Generic::Factory<Entity>::Create(pEntityType);
			newEntity->SetName(pEntityName);

			Adopt(*newEntity, sEntitiesKey);

			return *newEntity;
		}

		World& Sector::GetParentWorld() const
		{
			return *mParent;
		}

		void Sector::SetParentWorld(World& pWorld)
		{
			if (mParent != &pWorld)
			{
				pWorld.Adopt(*this, World::sSectorsKey);
			}
		}

		void Sector::Update(WorldState& pWorldState)
		{
			pWorldState;
		}
	}
}