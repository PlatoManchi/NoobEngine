#pragma once
#include "ActionList.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		class ActionListIf final : public ActionList
		{
			RTTI_DECLARATIONS(ActionListIf, ActionList)

			friend class Parsers::ActionParseHelper;
		public:
			static const char* sConditionKey;
			static const char* sThenActionKey;
			static const char* sElseActionKey;

			/**
				@brief Default constructor.
			*/
			ActionListIf();

			/**
				@brief Default destructor
			*/
			~ActionListIf();

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			void Update(WorldState& pWorldState) override;

			/**
				@brief Sets the condition value.
				@param[in] pConditionValue The condition that needs to be set.
			*/
			void SetCondition(int32_t pConditionValue);

			/**
				@brief Returns the value of the condition that is being used by this if.
				@return Integer that holds the condition value.
			*/
			int32_t GetCondition();

			/**
				@brief Set the then action who's update will be called if the condition satisfies.
				@param[in] pAction Reference to the action
			*/
			void SetThenAction(Action& pAction);

			/**
				@brief Get the then action which will be called if the condition satisfies.
				@return Pointer to the action.
			*/
			Action* GetThenAction();

			/**
				@brief Set the then action who's update will be called if the condition fails.
				@param[in] pAction Reference to the action
			*/
			void SetElseAction(Action& pAction);

			/**
				@brief Get the then action which will be called if the condition fails.
				@return Pointer to the action.
			*/
			Action* GetElseAction();
		private:
			/**
				@brief Populate all prescribed attributes for this attributed.
			*/
			void Populate();

			std::string mConditionKey;

			/**
				Caching the datums so as to avoid lookups
			*/
			Runtime::Datum* mConditionDatum;
			Runtime::Datum* mThenDatum;
			Runtime::Datum* mElseDatum;

			Runtime::Datum mValueDatum;
		};

		ActionFactory(ActionListIf)
	}
}