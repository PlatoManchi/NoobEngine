#include "pch.h"
#include "ActionTest.h"

namespace SupportingClasses
{
	RTTI_DEFINITIONS(ActionTest)

	ActionTest::ActionTest() :
		Action()
	{
		Populate();
	}


	ActionTest::~ActionTest()
	{
	}

	void ActionTest::Update(NoobEngine::GamePlay::WorldState& pWorldState)
	{
		pWorldState;
	}

	void ActionTest::Populate()
	{
		Action::Populate();
	}

}