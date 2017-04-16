#pragma once
#include "Reaction.h"
#include "Events/EventPublisher.h"
#include "WorldState.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		class ReactionAttributed : public Reaction
		{
			RTTI_DECLARATIONS(ReactionAttributed, Reaction)
		public:
			/**
				@brief Default constructor.
			*/
			ReactionAttributed();

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			virtual void Update(WorldState& pWorldState) override;

			/**
				@brief Notify is called when the event is expired.
				@param pPublisher The publisher that fired this event.
			*/
			virtual void Notify(Events::EventPublisher& pPublisher) override;

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

		protected:
			/**
				@brief Populate all the prescribed attributed.
			*/
			void Populate();

		private:
			/**
				String that holds the subtype of this event.
			*/
			std::string mSubtype;
		};

		ConcreteReactionFactory(ReactionAttributed)
	}
}
