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