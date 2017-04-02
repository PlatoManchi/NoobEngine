#include "pch.h"
#include "Sector.h"
#include "World.h"
#include "Entity.h"
#include "Parsers/WorldParseHelper.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(GamePlay::Sector)

		const char* Sector::sEntitiesKey = "Entities";

		Sector::Sector() :
			Attribute(), mParent(nullptr), mName("")
		{
			Populate();
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

			newEntity->SetParentSector(*this);

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
				mParent = &pWorld;
			}
		}

		void Sector::Update(WorldState& pWorldState)
		{
			Runtime::Datum& entitiesList = Entities();

			for (uint32_t i = 0; i < entitiesList.Size(); i++)
			{
				Entity* entity = reinterpret_cast<Entity*>(entitiesList.Get<Scope*>(i));
				pWorldState.mCurrentEntity = entity;

				entity->Update(pWorldState);
			}
		}

		void Sector::Populate()
		{
			Attribute::Populate();

			AppendPrescribedAttribute(Parsers::WorldParseHelper::sKeyAttribute).SetStorage(&mName, 1);
			AppendPrescribedAttribute(sEntitiesKey).SetType(Runtime::DatumType::TABLE);
		}
	}
}