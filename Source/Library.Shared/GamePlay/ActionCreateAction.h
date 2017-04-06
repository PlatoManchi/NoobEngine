#pragma once
#include "Action.h"
#include "Generic/Factory.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		class ActionCreateAction final : public Action
		{
			RTTI_DECLARATIONS(ActionCreateAction, Action)

			friend class Parsers::ActionParseHelper;
		public:
			/**
				@brief Default constructor
			*/
			ActionCreateAction();


			/**
				@brief Default destructor
			*/
			~ActionCreateAction();

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			virtual void Update(WorldState& pWorldState) override;

		private:
			/**
				@brief Populate all prescribed attributes for this attributed.
			*/
			void Populate();

			std::string mActionType;
			std::string mActionName;
		};

		ActionFactory(ActionCreateAction)
	}
}
