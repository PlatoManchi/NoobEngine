#include "pch.h"
#include "ActionPlayerDead.h"
#include <windows.h>

namespace SupportingClasses
{
	RTTI_DEFINITIONS(ActionPlayerDead)

		ActionPlayerDead::ActionPlayerDead() :
		Action()
	{
		Populate();
	}

	ActionPlayerDead::~ActionPlayerDead()
	{

	}

	void ActionPlayerDead::Update(NoobEngine::GamePlay::WorldState& pWorldState)
	{
		pWorldState;
		OutputDebugString("ActionPlayerDead\n");
	}

	void ActionPlayerDead::Populate()
	{
		Action::Populate();
	}
}