#include "pch.h"
#include "World.h"
#include "Sector.h"
#include "Parsers/WorldParseHelper.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(GamePlay::World)

		const char* World::sSectorsKey = "Sectors";

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
			return Append(sSectorsKey);
		}

		Sector& World::CreateSector(const std::string& pSectorName)
		{
			Sector* newSector = new Sector();
			newSector->SetName(pSectorName);

			newSector->SetParentWorld(*this);

			return *newSector;
		}

		void World::Update(WorldState& pWorldState)
		{
			Runtime::Datum& sectorsList = Sectors();
			pWorldState.mCurrentWorld = this;
			pWorldState.mCurrentSector = nullptr;
			pWorldState.mCurrentEntity = nullptr;
			pWorldState.mCurrentAction = nullptr;

			pWorldState.Update();

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
			AppendPrescribedAttribute(sSectorsKey).SetType(Runtime::DatumType::TABLE);
		}
	}
}