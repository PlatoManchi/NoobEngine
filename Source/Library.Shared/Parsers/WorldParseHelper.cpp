#include "pch.h"
#include "WorldParseHelper.h"

namespace NoobEngine
{
	namespace Parsers
	{
		WorldParseHelper::WorldParseHelper()
		{
		}

		WorldParseHelper::~WorldParseHelper()
		{
		}

		void WorldParseHelper::Initialize(XmlParseMaster* pXmlParseMaster)
		{
		}

		bool WorldParseHelper::StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes)
		{
			return false;
		}
		bool WorldParseHelper::EndElementHandler(const std::string& pElement)
		{
			return false;
		}
		IXmlParseHelper* WorldParseHelper::Clone() const
		{
			return nullptr;
		}
	}
}