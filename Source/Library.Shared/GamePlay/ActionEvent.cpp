#include "pch.h"
#include "ActionEvent.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(ActionEvent)

		ActionEvent::ActionEvent() :
			Action()
		{
			Populate();
		}

		void ActionEvent::Update(WorldState& pWorldState)
		{
			Action::Update(pWorldState);


		}

		void ActionEvent::Populate()
		{
			Action::Populate();

			AppendPrescribedAttribute("subtype").SetStorage(&mSubtype, 1);
			AppendPrescribedAttribute("delay").SetStorage(&mDelay, 1);
		}
	}
}