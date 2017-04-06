#include "pch.h"
#include "ActionList.h"
#include "WorldState.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(ActionList)

		const std::string ActionList::sActionListKey = "ActionListKey";

		ActionList::ActionList() :
			Action()
		{
			Populate();
		}

		ActionList::~ActionList()
		{
		}

		void ActionList::Update(WorldState& pWorldState)
		{
			Runtime::Datum& actions = Append(sActionListKey);

			for (uint32_t i = 0; i < actions.Size(); i++)
			{
				Action* action = reinterpret_cast<Action*>(actions.Get<Scope*>(i));
				action->Update(pWorldState);
			}
		}

		void ActionList::Populate()
		{
			Action::Populate();

			AppendPrescribedAttribute(sActionListKey).SetType(Runtime::DatumType::TABLE);
		}

		Action& ActionList::CreateAction(const std::string& pActionType, const std::string& pActionName)
		{
			Action* newAction = Generic::Factory<Action>::Create(pActionType);
			newAction->SetName(pActionName);

			newAction->SetParent(*this);

			return *newAction;
		}
	}
}