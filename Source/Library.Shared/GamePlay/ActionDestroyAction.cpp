#include "pch.h"
#include "ActionDestroyAction.h"
#include "WorldState.h"
#include "World.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(ActionDestroyAction)

		ActionDestroyAction::ActionDestroyAction() :
			Action()
		{
			Populate();
		}

		ActionDestroyAction::~ActionDestroyAction()
		{
		}

		void ActionDestroyAction::Update(WorldState& pWorldState)
		{
			std::string valueStr = operator[](Parsers::ActionParseHelper::sValueAttribute).Get<std::string>();
			Runtime::Datum* valueDatum = Search(sActionKey);
			//Runtime::Datum* valueDatum = pWorldState.mCurrentWorld->ResolveDatum(valueStr);
			
			if (valueDatum)
			{
				for (uint32_t i = 0; i < valueDatum->Size(); ++i)
				{
					Action* action = reinterpret_cast<Action*>(valueDatum->Get<Scope*>(i));

					if (action->Name() == valueStr)
					{
						pWorldState.mCurrentWorld->DestroyAction(*action);
					}
				}
			}
		}

		void ActionDestroyAction::Populate()
		{
			Action::Populate();
		}
	}
}