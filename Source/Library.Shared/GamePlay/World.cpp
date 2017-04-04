#include "pch.h"
#include "World.h"
#include "Sector.h"
#include "Parsers/WorldParseHelper.h"
#include "Action.h"
#include "Generic/Factory.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(GamePlay::World)

		World::World() :
			Attribute(), mName("")
		{
			Populate();
		}

		World::~World()
		{
		}

		std::string World::Name() const
		{
			return mName;
		}

		void World::SetName(const std::string& pName)
		{
			mName = pName;
		}

		Runtime::Datum& World::Sectors()
		{
			return Append(Sector::sSectorsKey);
		}

		Runtime::Datum& World::Actions()
		{
			return Append(Action::sActionKey);
		}

		Sector& World::CreateSector(const std::string& pSectorName)
		{
			Sector* newSector = new Sector();
			newSector->SetName(pSectorName);

			newSector->SetParentWorld(*this);

			return *newSector;
		}

		Action& World::CreateAction(const std::string& pActionType, const std::string& pActionName)
		{
			Action* newAction = Generic::Factory<Action>::Create(pActionType);
			newAction->SetName(pActionName);

			newAction->SetParent(*this);

			return *newAction;
		}

		void World::Update(WorldState& pWorldState)
		{
			Runtime::Datum& sectorsList = Sectors();
			pWorldState.mCurrentWorld = this;
			pWorldState.mCurrentSector = nullptr;
			pWorldState.mCurrentEntity = nullptr;
			pWorldState.mCurrentAction = nullptr;

			pWorldState.Update();

			// update all actions in world
			Runtime::Datum& actionsList = Actions();
			for (uint32_t i = 0; i < actionsList.Size(); i++)
			{
				Action* action = reinterpret_cast<Action*>(actionsList.Get<Action*>(i));
				pWorldState.mCurrentAction = action;

				action->Update(pWorldState);
			}

			// reset
			pWorldState.mCurrentAction = nullptr;

			// update all sectors in world
			for (uint32_t i = 0; i < sectorsList.Size(); i++)
			{
				Sector* sector = reinterpret_cast<Sector*>(sectorsList.Get<Scope*>(i));
				pWorldState.mCurrentSector = sector;

				sector->Update(pWorldState);
			}

			// reset
			pWorldState.mCurrentSector = nullptr;
		}

		void World::Populate()
		{
			Attribute::Populate();

			AppendPrescribedAttribute(Parsers::WorldParseHelper::sKeyAttribute).SetStorage(&mName, 1);
			AppendPrescribedAttribute(Sector::sSectorsKey).SetType(Runtime::DatumType::TABLE);
			AppendPrescribedAttribute(Action::sActionKey).SetType(Runtime::DatumType::TABLE);
		}
	}
}