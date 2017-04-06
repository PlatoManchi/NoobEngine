#include "pch.h"
#include "ActionListIf.h"
#include "World.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(ActionListIf)

		const char* ActionListIf::sConditionKey = "condition";
		const char* ActionListIf::sThenActionKey = "then";
		const char* ActionListIf::sElseActionKey = "else";

		ActionListIf::ActionListIf() :
			ActionList(), mConditionDatum(nullptr), mThenDatum(nullptr), mElseDatum(nullptr)
		{
			Populate();
		}

		ActionListIf::~ActionListIf()
		{
		}

		void ActionListIf::Update(WorldState& pWorldState)
		{
			if (!mConditionDatum)
			{
				//mConditionDatum = Search(mConditionKey);
				mConditionDatum = pWorldState.mCurrentWorld->ResolveDatum(mConditionKey);

				if (mConditionDatum)
				{
					if (mValueDatum.Type() == Runtime::DatumType::UNASSIGNED)
					{
						mValueDatum.SetType(mConditionDatum->Type());
						std::string valueStr = operator[](Parsers::ActionParseHelper::sValueAttribute).Get<std::string>();
						mValueDatum.SetFromString(valueStr);
					}
				}
			}
			
			if (mConditionDatum)
			{
				if (*mConditionDatum == mValueDatum)
				{
					GetThenAction()->Update(pWorldState);
				}
				else
				{
					GetElseAction()->Update(pWorldState);
				}
			}
		}

		void ActionListIf::SetCondition(int32_t pConditionValue)
		{
			*mConditionDatum = pConditionValue;
		}

		int32_t ActionListIf::GetCondition()
		{
			return mConditionDatum->Get<int32_t>();
		}

		void ActionListIf::SetThenAction(Action& pAction)
		{
			Adopt(pAction, sThenActionKey);
			pAction.mParent = this;
		}

		Action* ActionListIf::GetThenAction()
		{
			if (mThenDatum->Size() > 0)
			{
				return reinterpret_cast<Action*>(mThenDatum->Get<Scope*>());
			}
			return nullptr;
		}

		void ActionListIf::SetElseAction(Action& pAction)
		{
			Adopt(pAction, sElseActionKey);
			pAction.mParent = this;
		}

		Action* ActionListIf::GetElseAction()
		{
			if (mElseDatum->Size() > 0)
			{
				return reinterpret_cast<Action*>(mElseDatum->Get<Scope*>());
			}
			return nullptr;
		}

		void ActionListIf::Populate()
		{
			ActionList::Populate();
			
			mThenDatum = &AppendPrescribedAttribute(sThenActionKey);
			mThenDatum->SetType(Runtime::DatumType::TABLE);

			mElseDatum = &AppendPrescribedAttribute(sElseActionKey);
			mElseDatum->SetType(Runtime::DatumType::TABLE);
		}
	}
}