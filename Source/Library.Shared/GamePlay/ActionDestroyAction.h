#pragma once
#include "Action.h"
#include "Generic/Factory.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		class ActionDestroyAction final : public Action
		{
			RTTI_DECLARATIONS(ActionDestroyAction, Action)

		public:
			/**
				@brief Default constructor
			*/
			ActionDestroyAction();

			/**
				@brief Default destructor
			*/
			~ActionDestroyAction();

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			void Update(WorldState& pWorldState) override;
		private:
			/**
				Populate all prescribed attributes
			*/
			void Populate();
		};

		ActionFactory(ActionDestroyAction)
	}
}