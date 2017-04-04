#include "pch.h"
#include "ActionList.h"
#include "WorldState.h"

namespace NoobEngine
{
	namespace GamePlay
	{
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
	}
}