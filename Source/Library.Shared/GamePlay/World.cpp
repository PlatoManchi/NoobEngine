#include "pch.h"
#include "World.h"
#include "Sector.h"

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
			pWorldState;
		}

		void World::Populate()
		{
			Attribute::Populate();

			AppendPrescribedAttribute("name").SetStorage(&mName, 1);
			AppendPrescribedAttribute(sSectorsKey).SetType(Runtime::DatumType::TABLE);
		}
	}
}