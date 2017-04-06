#pragma once
#include "GamePlay/Action.h"
#include "GamePlay/WorldState.h"
#include "Generic/Factory.h"

namespace SupportingClasses
{
	class ActionPlayerDead final : public NoobEngine::GamePlay::Action
	{
		RTTI_DECLARATIONS(ActionPlayerDead, NoobEngine::GamePlay::Action)
	public:

		ActionPlayerDead();

		~ActionPlayerDead();

		/**
			@brief Called every frame.
			@param[in] pWorldState Reference to the world state of current game.
		*/
		virtual void Update(NoobEngine::GamePlay::WorldState& pWorldState);

		void Populate();
	};

	ActionFactory(ActionPlayerDead)
}
