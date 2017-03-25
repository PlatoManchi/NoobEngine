#include "pch.h"
#include "XmlParseHelperConstruction.h"
#include "XmlSharedData.h"
#include "Utils/Utils.h"

namespace NoobEngine
{
	namespace Parsers
	{
		XmlParseHelperConstruction::XmlParseHelperConstruction()
		{ }

		XmlParseHelperConstruction::~XmlParseHelperConstruction()
		{ }

		void XmlParseHelperConstruction::Initialize(XmlParseMaster* pXmlParseMaster)
		{
			IXmlParseHelper::Initialize(pXmlParseMaster);

			if (mXmlParseMaster->GetSharedData())
			{
				if (mXmlParseMaster->GetSharedData()->Is(XmlSharedData::TypeIdClass()))
				{

				}
				else
				{
					throw std::exception("Invalid SharedData.");
				}
			}
		}

		bool XmlParseHelperConstruction::StartElementHandler(const std::string & pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes)
		{
			pAttributes;
			XmlSharedData* sharedData = reinterpret_cast<XmlSharedData*>(mXmlParseMaster->GetSharedData());

			if (Utils::StrNCaseCmp(pElement, "construction"))
			{
				sharedData->mIsConstructionPhase = true;
			}

			
			if (sharedData->mIsConstructionPhase)
			{

			}
			return false;
		}

		bool XmlParseHelperConstruction::EndElementHandler(const std::string & pElement)
		{
			XmlSharedData* sharedData = reinterpret_cast<XmlSharedData*>(mXmlParseMaster->GetSharedData());

			if (Utils::StrNCaseCmp(pElement, "construction"))
			{
				sharedData->mIsConstructionPhase = false;
			}

			if (sharedData->mIsConstructionPhase)
			{

			}
			return false;
		}


	}
}