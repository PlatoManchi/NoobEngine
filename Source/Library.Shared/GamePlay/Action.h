#pragma once
#include "Runtime/Attribute.h"
#include "WorldState.h"
#include "Parsers/ActionParseHelper.h"
#include "Parsers/ReactionParseHelper.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		class ActionList;

		class Action : public Runtime::Attribute
		{
			RTTI_DECLARATIONS(Action, Attribute)

			friend class Parsers::ActionParseHelper;
			friend class Parsers::ReactionParseHelper;
			friend class ActionListIf;
		public:
			static const char* sActionKey;
			static const char* sKeyAttribute;
			/**
				@brief Default constructor.
			*/
			Action();

			/**
				@brief Default destructor.
			*/
			virtual ~Action();

			/**
				@brief Return the name of the action.
				@return String that holds the name of this action
			*/
			std::string Name();

			/**
				@brief Set the name of this action.
				@param[in] pName String that holds the name to be set for this action.
			*/
			void SetName(std::string pName);

			/**
				@brief Get the parent of this action
				@return 
			*/
			Attribute& GetParent() const;

			/**
				@brief Set the parent of this action
				@details The pParent has to be of type World or Sector or Entity or ActionList.
				@param[in] pParent The attributed that is supposed to the parent of this action.
			*/
			void SetParent(ActionList& pParent);

			/**
				@brief Set the parent of this action
				@details The pParent has to be of type World or Sector or Entity or ActionList.
				@param[in] pParent The attributed that is supposed to the parent of this action.
			*/
			void SetParent(Entity& pParent);

			/**
				@brief Set the parent of this action
				@details The pParent has to be of type World or Sector or Entity or ActionList.
				@param[in] pParent The attributed that is supposed to the parent of this action.
			*/

			void SetParent(Sector& pParent);
			/**
				@brief Set the parent of this action
				@details The pParent has to be of type World or Sector or Entity or ActionList.
				@param[in] pParent The attributed that is supposed to the parent of this action.
			*/
			void SetParent(World& pParent);

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			virtual void Update(WorldState& pWorldState) = 0;

			
		protected:
			/**
				@brief Populate all prescribed attributes to attributed
			*/
			void Populate();

			/**
				Holds the name of this action
			*/
			std::string mName;

			/**
				Holds the pointer to the parent scope
			*/
			Attribute* mParent;

			/**
				@brief Set the parent of this action
				@details The pParent has to be of type World or Sector or Entity.
				@param[in] pParent The attributed that is supposed to the parent of this action.
			*/
			virtual void SetParent(Attribute* pParent);
		};
	}
}

#define ActionFactory(ConcreteAction)	ConcreteFactory(NoobEngine::GamePlay::Action, ConcreteAction)