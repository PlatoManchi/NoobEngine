#include "pch.h"
#include "Sector.h"

namespace NoobEngine
{
	namespace GamePlay
	{
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

		Runtime::Datum& Sector::Entities() const
		{
			// TODO: insert return statement here
		}

		Entity& Sector::CreateEntity(const std::string& pEntityType, const std::string& pEntityName)
		{
			// TODO: insert return statement here
		}

		World& Sector::GetWorld() const
		{
			// TODO: insert return statement here
		}

		void Sector::SetWorld(const World& pWorld)
		{
		}

		void Sector::Update(WorldState& pWorldState)
		{
			pWorldState;
		}


	}
}