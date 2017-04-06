#include "pch.h"
#include "ActionPlayerAlive.h"
#include <windows.h>

namespace SupportingClasses
{
	RTTI_DEFINITIONS(ActionPlayerAlive)

	ActionPlayerAlive::ActionPlayerAlive() :
		Action()
	{
		Populate();
	}

	ActionPlayerAlive::~ActionPlayerAlive()
	{

	}

	void ActionPlayerAlive::Update(NoobEngine::GamePlay::WorldState& pWorldState)
	{
		pWorldState;
		OutputDebugString("ActionPlayerAlive\n");
	}

	void ActionPlayerAlive::Populate()
	{
		Action::Populate();
	}
}