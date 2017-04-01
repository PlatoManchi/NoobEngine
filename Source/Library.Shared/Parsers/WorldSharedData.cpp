#include "pch.h"
#include "WorldSharedData.h"

namespace NoobEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(WorldSharedData)

		WorldSharedData::WorldSharedData() :
			XmlSharedData()
		{

		}

		WorldSharedData::~WorldSharedData()
		{

		}

		XmlParseMaster::SharedData* WorldSharedData::Clone() const
		{
			return nullptr;
		}
	}
}