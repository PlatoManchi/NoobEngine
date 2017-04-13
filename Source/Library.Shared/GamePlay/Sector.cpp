#include "pch.h"
#include "Sector.h"
#include "World.h"
#include "Entity.h"
#include "Parsers/WorldParseHelper.h"
#include "ActionListIf.h"
namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(GamePlay::Sector)

		const char* Sector::sSectorsKey = "Sectors";

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
			return Append(Entity::sEntitiesKey);
		}

		Runtime::Datum & Sector::Actions()
		{
			return Append(Action::sActionKey);
		}

		Entity& Sector::CreateEntity(const std::string& pEntityType, const std::string& pEntityName)
		{
			Entity* newEntity = Generic::Factory<Entity>::Create(pEntityType);
			newEntity->SetName(pEntityName);

			newEntity->SetParentSector(*this);

			return *newEntity;
		}

		Action& Sector::CreateAction(const std::string& pActionType, const std::string& pActionName)
		{
			Action* newAction = Generic::Factory<Action>::Create(pActionType);
			newAction->SetName(pActionName);

			newAction->SetParent(*this);

			return *newAction;
		}

		World& Sector::GetParentWorld() const
		{
			return *mParent;
		}

		void Sector::SetParentWorld(World& pWorld)
		{
			if (mParent != &pWorld)
			{
				pWorld.Adopt(*this, Sector::sSectorsKey);
				mParent = &pWorld;
			}
		}

		void Sector::Update(WorldState& pWorldState)
		{
			// update all actions in sector
			Runtime::Datum& actionsList = Actions();
			for (uint32_t i = 0; i < actionsList.Size(); ++i)
			{
				Action* action = static_cast<Action*>(actionsList.Get<Scope*>(i));
				pWorldState.mCurrentAction = action;

				action->Update(pWorldState);
			}

			// reset
			pWorldState.mCurrentAction = nullptr;

			// updating all entities in the sector
			Runtime::Datum& entitiesList = Entities();
			for (uint32_t i = 0; i < entitiesList.Size(); ++i)
			{
				Entity* entity = reinterpret_cast<Entity*>(entitiesList.Get<Scope*>(i));
				pWorldState.mCurrentEntity = entity;

				entity->Update(pWorldState);
			}

			// reset
			pWorldState.mCurrentEntity = nullptr;
		}

		void Sector::Populate()
		{
			Attribute::Populate();

			AppendPrescribedAttribute(Parsers::WorldParseHelper::sKeyAttribute).SetStorage(&mName, 1);
			AppendPrescribedAttribute(Entity::sEntitiesKey).SetType(Runtime::DatumType::TABLE);
			AppendPrescribedAttribute(Action::sActionKey).SetType(Runtime::DatumType::TABLE);
		}
	}
}