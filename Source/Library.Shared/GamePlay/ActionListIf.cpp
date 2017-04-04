#include "pch.h"
#include "ActionListIf.h"

namespace NoobEngine
{
	namespace GamePlay
	{
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
			if (GetCondition())
			{
				GetThenAction()->Update(pWorldState);
			}
			else
			{
				GetElseAction()->Update(pWorldState);
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
			*mThenDatum = &pAction;
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
			*mElseDatum = &pAction;
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

			mConditionDatum = &AddInternalAttribute(sConditionKey, 0);
			
			mThenDatum = &AppendPrescribedAttribute(sThenActionKey);
			mThenDatum->SetType(Runtime::DatumType::TABLE);

			mElseDatum = &AppendPrescribedAttribute(sElseActionKey);
			mElseDatum->SetType(Runtime::DatumType::TABLE);
		}
	}
}