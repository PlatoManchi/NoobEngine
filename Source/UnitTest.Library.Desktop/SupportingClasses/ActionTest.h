#pragma once
#include "GamePlay/Action.h"
#include "Generic/Factory.h"

namespace SupportingClasses
{
	class ActionTest final : public NoobEngine::GamePlay::Action
	{
		RTTI_DECLARATIONS(ActionTest, Action)

	public:
		/**
		@brief Default constructor.
		*/
		ActionTest();

		/**
		@brief Default destructor
		*/
		~ActionTest();

		/**
		@brief Called every frame.
		@param[in] pWorldState Reference to the world state of current game.
		*/
		virtual void Update(NoobEngine::GamePlay::WorldState& pWorldState);


	private:
		/**
			@brief Populate all prescribed attributes for this attributed.
		*/
		void Populate();

	};

	ActionFactory(ActionTest)
	
}