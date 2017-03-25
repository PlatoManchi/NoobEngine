#include "pch.h"
#include "XmlSharedData.h"

namespace NoobEngine
{
	namespace Parsers
	{
		XmlSharedData::XmlSharedData() : 
			XmlParseHelperTable::XmlTableParser()
		{ }

		XmlSharedData::~XmlSharedData()
		{ }

		XmlParseMaster::SharedData* XmlSharedData::Clone() const
		{
			XmlSharedData* cloneHelper = new XmlSharedData();
			return cloneHelper;
		}
	}
}