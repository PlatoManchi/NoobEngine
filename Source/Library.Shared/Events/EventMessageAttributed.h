#pragma once
#include "Runtime/Attribute.h"
#include "GamePlay/World.h"

namespace NoobEngine
{
	namespace Events
	{
		class EventMessageAttributed : public Runtime::Attribute
		{
			RTTI_DECLARATIONS(EventMessageAttributed, Attribute)
		public:
			/**
				@brief Default constructor
			*/
			EventMessageAttributed();

			/**
				@brief Returns the subtype of current message.
				@return String that holds the subtype.
			*/
			std::string GetSubtype() const;

			/**
				@brief Sets the subtype of this.
				@param[in] pSubtype Reference to the string that holds the subtype.
			*/
			void SetSubtype(const std::string& pSubtype);

			/**
				@brief Returns the pointer that points to the world that this event belongs to.
				@return Pointer to world.
			*/
			GamePlay::World* GetWorld() const;

			/**
				@brief Sets the world of this event.
				@param[in] pWorld Reference to the current world object.
			*/
			void SetWorld(GamePlay::World& pWorld);
		protected:
			/**
				string that holds the subtype of this event.
			*/
			std::string mSubtype;

			/**
				Pointer that points to the current world.
			*/
			GamePlay::World* mWorld;

			/**
				Populate all prescribed attributes.
			*/
			void Populate();
			
		};
	}
}