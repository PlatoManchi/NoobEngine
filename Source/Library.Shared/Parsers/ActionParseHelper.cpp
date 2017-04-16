#include "pch.h"
#include "ActionParseHelper.h"
#include "WorldSharedData.h"
#include "Utils/Utils.h"
#include "GamePlay/Action.h"
#include "Generic/Factory.h"
#include "GamePlay/ActionListIf.h"
#include "GamePlay/ActionDecrement.h"
#include "GamePlay/ActionCreateAction.h"
#include "GamePlay/ActionDestroyAction.h"
#include "GamePlay/ActionList.h"

namespace NoobEngine
{
	namespace Parsers
	{

		const std::string ActionParseHelper::sActionTag = "action";
		const std::string ActionParseHelper::sConditionAttribute = "condition";
		const std::string ActionParseHelper::sClassAttribute = "class";
		const std::string ActionParseHelper::sKeyAttribute = "key";
		const std::string ActionParseHelper::sValueAttribute = "value";

		// if
		const std::string ActionParseHelper::sIfTag = "if";
		const std::string ActionParseHelper::sThenTag = "then";
		const std::string ActionParseHelper::sElseTag = "else";

		// switch
		const std::string ActionParseHelper::sSwitchTag = "switch";
		const std::string ActionParseHelper::sValueTag = "value";

		// while
		const std::string ActionParseHelper::sWhileTag = "while";

		// for each
		const std::string ActionParseHelper::sForEachTag = "foreach";

		// decrement
		const std::string ActionParseHelper::sDecrementTag = "decrement";

		// create action
		const std::string ActionParseHelper::sCreateActionTag = "createaction";

		// destroy action
		const std::string ActionParseHelper::sDestroyActionTag = "destroyaction";

		ActionParseHelper::ActionParseHelper() :
			IXmlParseHelper(), mActionDepth(0), mIsValidIf(false)
		{
		}

		ActionParseHelper::~ActionParseHelper()
		{
		}

		void ActionParseHelper::Initialize(XmlParseMaster& pXmlParseMaster)
		{
			IXmlParseHelper::Initialize(pXmlParseMaster);

			if (mXmlParseMaster->GetSharedData())
			{
				if (!mXmlParseMaster->GetSharedData()->Is(WorldSharedData::TypeIdClass()))
				{
					throw std::exception("Invalid SharedData.");
				}
			}
		}

		bool ActionParseHelper::StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes)
		{
			WorldSharedData* sharedData = reinterpret_cast<WorldSharedData*>(mXmlParseMaster->GetSharedData());
			
			if (sharedData->mHasValidRoot && !sharedData->mIsConstructionPhase)
			{
				if (Utils::StrNCaseCmp(pElement, sActionTag))
				{
					assert(pAttributes.ContainsKey(sClassAttribute));

					++mActionDepth;
					Runtime::Attribute* currentAttrib = sharedData->GetCurrentNode().As<Runtime::Attribute>();
					if (currentAttrib)
					{
						if (!sharedData->mIsActionList)
						{
							GamePlay::Action* action = Generic::Factory<GamePlay::Action>::Create(pAttributes[sClassAttribute]);

							action->SetParent(currentAttrib);

							if (pAttributes.ContainsKey(sKeyAttribute))
							{
								action->SetName(pAttributes[sKeyAttribute]);
							}

							sharedData->mCurrentRoot = action;
						}
						else
						{
							// if action list
							GamePlay::ActionList* parentAction = currentAttrib->As<GamePlay::ActionList>();
							GamePlay::Action* childAction = &parentAction->CreateAction(pAttributes[sClassAttribute], pAttributes[sKeyAttribute]);
							//GamePlay::ActionList* childAction = static_cast<GamePlay::ActionList*>(Generic::Factory<GamePlay::Action>::Create(pAttributes[sClassAttribute]));
							childAction->SetName(pAttributes[sKeyAttribute]);

							for (std::pair<std::string, std::string> pair : pAttributes)
							{
								if (!Utils::StrNCaseCmp(pair.first, sClassAttribute))
								{
									(*childAction)[pair.first] = pair.second;
								}
							}
							childAction->SetParent(currentAttrib);
						}
					}
					
					return true;
				}
				else if (Utils::StrNCaseCmp(pElement, sCreateActionTag))
				{
					assert(pAttributes.ContainsKey(sKeyAttribute) && pAttributes.ContainsKey(sClassAttribute) && pAttributes.ContainsKey(sValueTag));

					Runtime::Attribute* currentAttrib = sharedData->GetCurrentNode().As<Runtime::Attribute>();

					if (currentAttrib)
					{
						GamePlay::ActionCreateAction* action = reinterpret_cast<GamePlay::ActionCreateAction*>(Generic::Factory<GamePlay::Action>::Create("ActionCreateAction"));
						action->SetName(pAttributes[sKeyAttribute]);
						action->SetParent(currentAttrib);

						action->mActionType = pAttributes[sClassAttribute];
						action->mActionName = pAttributes[sValueTag];
					}
					
					return true;
				}

				else if (Utils::StrNCaseCmp(pElement, sDestroyActionTag))
				{
					assert(pAttributes.ContainsKey(sKeyAttribute) && pAttributes.ContainsKey(sValueAttribute));

					Runtime::Attribute* currentAttrib = sharedData->GetCurrentNode().As<Runtime::Attribute>();

					if (currentAttrib)
					{
						GamePlay::ActionDestroyAction* action = reinterpret_cast<GamePlay::ActionDestroyAction*>(Generic::Factory<GamePlay::Action>::Create("ActionDestroyAction"));
						action->SetName(pAttributes[sKeyAttribute]);
						action->SetParent(currentAttrib);

						(*action)[sKeyAttribute] = pAttributes[sKeyAttribute];
						(*action)[sValueAttribute] = pAttributes[sValueAttribute];
					}

					return true;
				}

				else if (Utils::StrNCaseCmp(pElement, sIfTag))
				{

					assert(pAttributes.ContainsKey(sKeyAttribute) && pAttributes.ContainsKey(sConditionAttribute) && pAttributes.ContainsKey(sValueAttribute));

					++mActionDepth;
					mIsValidIf = true;

					Runtime::Attribute* currentAttrib = sharedData->GetCurrentNode().As<Runtime::Attribute>();

					if (currentAttrib)
					{
						GamePlay::ActionListIf* ifAction = reinterpret_cast<GamePlay::ActionListIf*>(Generic::Factory<GamePlay::Action>::Create("ActionListIf"));
						ifAction->SetName(pAttributes[sKeyAttribute]);
						(*ifAction)[sValueAttribute] = pAttributes[sValueAttribute];

						ifAction->SetParent(currentAttrib);
						ifAction->mConditionKey = pAttributes[sConditionAttribute];

						sharedData->mCurrentRoot = ifAction;
					}

					return true;
				}

				else if ( mIsValidIf && Utils::StrNCaseCmp(pElement, sThenTag))
				{
					assert(pAttributes.ContainsKey(sClassAttribute));

					GamePlay::ActionListIf* ifAction = reinterpret_cast<GamePlay::ActionListIf*>(sharedData->mCurrentRoot);
					GamePlay::Action* thenAction = Generic::Factory<GamePlay::Action>::Create(pAttributes[sClassAttribute]);

					for (std::pair<std::string, std::string> pair : pAttributes)
					{
						if (!Utils::StrNCaseCmp(pair.first, sClassAttribute))
						{
							(*thenAction)[pair.first] = pair.second;
						}
					}

					ifAction->SetThenAction(*thenAction);

					return true;
				}
				else if (mIsValidIf && Utils::StrNCaseCmp(pElement, sElseTag))
				{
					assert(pAttributes.ContainsKey(sClassAttribute));

					GamePlay::ActionListIf* ifAction = reinterpret_cast<GamePlay::ActionListIf*>(sharedData->mCurrentRoot);
					GamePlay::Action* elseAction = Generic::Factory<GamePlay::Action>::Create(pAttributes[sClassAttribute]);

					for (std::pair<std::string, std::string> pair : pAttributes)
					{
						if (!Utils::StrNCaseCmp(pair.first, sClassAttribute))
						{
							(*elseAction)[pair.first] = pair.second;
						}
					}

					ifAction->SetElseAction(*elseAction);

					return true;
				}

				else if (Utils::StrNCaseCmp(pElement, sDecrementTag))
				{
					assert(pAttributes.ContainsKey(sKeyAttribute) && pAttributes.ContainsKey(sValueAttribute));

					Runtime::Attribute* currentAttrib = sharedData->GetCurrentNode().As<Runtime::Attribute>();

					if (currentAttrib)
					{
						GamePlay::ActionDecrement* decrementAction = reinterpret_cast<GamePlay::ActionDecrement*>(Generic::Factory<GamePlay::Action>::Create("ActionDecrement"));
						decrementAction->mValueKey = pAttributes[sValueAttribute];
						decrementAction->SetName(pAttributes[sKeyAttribute]);
						decrementAction->SetParent(currentAttrib);
					}
				}
			}

			return false;
		}

		bool ActionParseHelper::EndElementHandler(const std::string& pElement)
		{
			WorldSharedData* sharedData = reinterpret_cast<WorldSharedData*>(mXmlParseMaster->GetSharedData());

			if (Utils::StrNCaseCmp(pElement, sActionTag))
			{
				--mActionDepth;
				sharedData->mCurrentRoot = sharedData->mCurrentRoot->GetParent();
				return true;
			}
			else if (Utils::StrNCaseCmp(pElement, sCreateActionTag))
			{
				return true;
			}
			else if (mIsValidIf && Utils::StrNCaseCmp(pElement, sIfTag))
			{
				--mActionDepth;
				mIsValidIf = false;
				sharedData->mCurrentRoot = sharedData->mCurrentRoot->GetParent();
				return true;
			}
			else if (mIsValidIf && Utils::StrNCaseCmp(pElement, sThenTag))
			{
				return true;
			}
			else if (mIsValidIf && Utils::StrNCaseCmp(pElement, sElseTag))
			{
				return true;
			}

			return false;
		}

		IXmlParseHelper* ActionParseHelper::Clone() const
		{
			return nullptr;
		}
	}
}