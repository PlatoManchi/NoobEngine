#include "pch.h"
#include "ReactionParseHelper.h"
#include "WorldSharedData.h"
#include "Utils/Utils.h"

namespace NoobEngine
{
	namespace Parsers
	{
		const std::string ReactionParseHelper::sActionEventTag = "actionevent";
		const std::string ReactionParseHelper::sReactionTag = "reaction";
		const std::string ReactionParseHelper::sKeyAttribute = "key";
		const std::string ReactionParseHelper::sSubtypeAttribute = "subtype";

		ReactionParseHelper::ReactionParseHelper()
		{

		}

		ReactionParseHelper::~ReactionParseHelper()
		{

		}

		void ReactionParseHelper::Initialize(XmlParseMaster& pXmlParseMaster)
		{
			IXmlParseHelper::Initialize(pXmlParseMaster);
			// checking if the shared data is valid
			if (mXmlParseMaster->GetSharedData())
			{
				if (!mXmlParseMaster->GetSharedData()->Is(WorldSharedData::TypeIdClass()))
				{
					throw std::exception("Invalid SharedData.");
				}
			}
		}

		bool ReactionParseHelper::StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes)
		{
			WorldSharedData* sharedData = reinterpret_cast<WorldSharedData*>(mXmlParseMaster->GetSharedData());

			if (sharedData->mHasValidRoot && !sharedData->mIsConstructionPhase)
			{

			}
			return false;
		}

		bool ReactionParseHelper::EndElementHandler(const std::string& pElement)
		{
			return false;
		}

		IXmlParseHelper* ReactionParseHelper::Clone() const
		{
			ReactionParseHelper* clonedHelper = new ReactionParseHelper();
			return clonedHelper;
		}


	}
}