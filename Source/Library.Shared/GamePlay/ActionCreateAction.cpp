#include "pch.h"
#include "ActionCreateAction.h"
#include "WorldState.h"
#include "Entity.h"


namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(ActionCreateAction)

		ActionCreateAction::ActionCreateAction() :
			Action()
		{
			Populate();
		}

		ActionCreateAction::~ActionCreateAction()
		{

		}

		void ActionCreateAction::Update(WorldState& pWorldState)
		{
			if (pWorldState.mCurrentEntity)
			{
				pWorldState.mCurrentEntity->CreateAction(mActionType, mActionName);
			}
		}

		void ActionCreateAction::Populate()
		{
			Action::Populate();
		}
	}
}