#include "pch.h"
#include "XmlSharedData.h"

namespace NoobEngine
{
	namespace Parsers
	{
		XmlSharedData::XmlSharedData() : 
			XmlParseHelperTable::XmlTableParser(), mCurrentPrototype("")
		{ }

		XmlSharedData::~XmlSharedData()
		{
			// deleting all prototypes
			for (std::pair<std::string, Runtime::Scope*> element : mPrototypeScopes)
			{
				delete element.second;
			}
		}

		XmlParseMaster::SharedData* XmlSharedData::Clone() const
		{
			XmlSharedData* cloneHelper = new XmlSharedData();
			return cloneHelper;
		}
	}
}