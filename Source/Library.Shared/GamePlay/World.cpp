#include "pch.h"
#include "World.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		World::World()
		{
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

		Runtime::Datum& World::Sectors() const
		{
			// TODO: insert return statement here
		}

		Sector& World::CreateSector(const std::string& pSectorName)
		{
			// TODO: insert return statement here
		}

		void World::Update(WorldState& pWorldState)
		{
			pWorldState;
		}
	}
}