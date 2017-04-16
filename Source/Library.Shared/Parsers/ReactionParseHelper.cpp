#include "pch.h"
#include "ReactionParseHelper.h"
#include "WorldSharedData.h"
#include "Utils/Utils.h"
#include "GamePlay/ActionEvent.h"
#include "GamePlay/ReactionAttributed.h"
#include "Generic/Factory.h"

namespace NoobEngine
{
	namespace Parsers
	{
		const std::string ReactionParseHelper::sActionEventTag = "actionevent";
		const std::string ReactionParseHelper::sReactionTag = "reaction";
		const std::string ReactionParseHelper::sKeyAttribute = "key";
		const std::string ReactionParseHelper::sSubtypeAttribute = "subtype";
		const std::string ReactionParseHelper::sDelayAttribute = "delay";

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
			WorldSharedData* sharedData = static_cast<WorldSharedData*>(mXmlParseMaster->GetSharedData());

			if (sharedData->mHasValidRoot && !sharedData->mIsConstructionPhase)
			{
				if (Utils::StrNCaseCmp(pElement, sActionEventTag) && pAttributes.ContainsKey(sSubtypeAttribute) && pAttributes.ContainsKey(sKeyAttribute))
				{
					mIsValidActionEvent = true;

					Runtime::Attribute* currentAttrib = sharedData->GetCurrentNode().As<Runtime::Attribute>();
					if (currentAttrib)
					{
						GamePlay::ActionEvent* action = static_cast<GamePlay::ActionEvent*>(Generic::Factory<GamePlay::Action>::Create("ActionEvent"));
						action->SetName(pAttributes[sKeyAttribute]);
						action->SetParent(currentAttrib);
						action->SetSubtype(pAttributes[sSubtypeAttribute]);

						// if there is delay attribute then set the delay else set the delay to 0sec
						float delay = 0.0f;
						if (pAttributes.ContainsKey(sDelayAttribute))
						{
							delay = stof(pAttributes[sDelayAttribute]);
						}
						action->SetDelay(delay);

						sharedData->mCurrentRoot = action;
					}
					return true;
				}
				else if (Utils::StrNCaseCmp(pElement, sReactionTag) && pAttributes.ContainsKey(sSubtypeAttribute) && pAttributes.ContainsKey(sKeyAttribute))
				{
					mIsValidReaction = true;
					Runtime::Attribute* currentAttrib = sharedData->GetCurrentNode().As<Runtime::Attribute>();
					sharedData->mIsActionList = true;

					if (currentAttrib)
					{
						GamePlay::ReactionAttributed* reactionAttributed = static_cast<GamePlay::ReactionAttributed*>(Generic::Factory<GamePlay::Reaction>::Create("ReactionAttributed"));
						reactionAttributed->SetName(pAttributes[sKeyAttribute]);
						reactionAttributed->SetParent(currentAttrib);
						reactionAttributed->SetSubtype(pAttributes[sSubtypeAttribute]);

						sharedData->mCurrentRoot = reactionAttributed;
					}

					return true;
				}
			} // end of validation if

			
			return false;
		}

		bool ReactionParseHelper::EndElementHandler(const std::string& pElement)
		{
			WorldSharedData* sharedData = static_cast<WorldSharedData*>(mXmlParseMaster->GetSharedData());

			if (Utils::StrNCaseCmp(pElement, sActionEventTag) && mIsValidActionEvent)
			{
				mIsValidActionEvent = false;
				sharedData->mCurrentRoot = sharedData->mCurrentRoot->GetParent();
				return true;
			}
			else if (Utils::StrNCaseCmp(pElement, sReactionTag) && mIsValidReaction)
			{
				mIsValidReaction = false;
				sharedData->mIsActionList = false;
				sharedData->mCurrentRoot = sharedData->mCurrentRoot->GetParent();
				return true;
			}

			return false;
		}

		IXmlParseHelper* ReactionParseHelper::Clone() const
		{
			ReactionParseHelper* clonedHelper = new ReactionParseHelper();
			return clonedHelper;
		}


	}
}