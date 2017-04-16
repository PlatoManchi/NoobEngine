#pragma once
#include "Action.h"
#include "Generic/Factory.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		class ActionEvent : public Action
		{
			RTTI_DECLARATIONS(ActionEvent, Action)
		public:
			/**
				@brief Default constructor.
			*/
			ActionEvent();

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			virtual void Update(WorldState& pWorldState);

			/**
				@brief Return the string that holds the subtype.
				@return String
			*/
			std::string GetSubtype() const;

			/**
				@brief Set the subtype of the ActionEvent.
				@param[in] pSubtype String that holds the subtype value
			*/
			void SetSubtype(const std::string& pSubtype);

			/**
				@brief Return the delay of the ActionEvent
				@return float
			*/
			float GetDelay() const;

			/**
				@brief Set the delay for ActionEvent
				@param[in] pDelay float that holds the delay.
			*/
			void SetDelay(float pDelay);
		protected:
			/**
				@brief Populate all the prescribed attributes.
			*/
			void Populate();

		private:
			/**
				String that holds the subtype that is used to filter the events.
			*/
			std::string mSubtype;

			/**
				Delay in seconds.
			*/
			float mDelay;
		};

		ActionFactory(ActionEvent)
	}
}