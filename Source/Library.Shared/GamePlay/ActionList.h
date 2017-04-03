#pragma once
#include "Action.h"
#include "Generic/Factory.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		class ActionList : public Action
		{
		public:
			static const std::string sActionListKey;

			/**
				@brief Default constructor
			*/
			ActionList();

			/**
				@brief Default destructor
			*/
			virtual ~ActionList();

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			virtual void Update(WorldState& pWorldState) override;

			/**
				@brief Populate all prescribed attributes to attributed
			*/
			void Populate();
		};
		
		ActionFactory(ActionList)
	}
}