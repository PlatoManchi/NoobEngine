#pragma once
#include "Action.h"
#include "Generic/Factory.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		class ActionList : public Action
		{
			RTTI_DECLARATIONS(ActionList, Action)
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
				@brief Create a new action, adopt it into this entity and return the reference to the action that is created.
				@param[in] pActionType Type of action that needs to be created. This is usually the class name of the action.
				@param[in] pActionName The name to be assigned to the action.
				@return Reference to action that is created.
			*/
			Action& CreateAction(const std::string& pActionType, const std::string& pActionName);

		protected:
			/**
				@brief Populate all prescribed attributes to attributed
			*/
			void Populate();
		};
		
		ActionFactory(ActionList)
	}
}