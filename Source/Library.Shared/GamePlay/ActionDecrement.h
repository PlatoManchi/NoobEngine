#pragma once
#include "Action.h"
#include "Generic/Factory.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		class ActionDecrement final : public Action
		{
			RTTI_DECLARATIONS(ActionDecrement, Action)

			friend class Parsers::ActionParseHelper;
		public:
			/**
				@brief Default constructor.
			*/
			ActionDecrement();

			/**
				@brief Default destructor
			*/
			~ActionDecrement();

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

			/**
				The string key whose value needs to be decremented
			*/
			std::string mValueKey;

			/**
				Caching datum
			*/
			Runtime::Datum* mValueDatum;
		};

		ActionFactory(ActionDecrement)
	}
}