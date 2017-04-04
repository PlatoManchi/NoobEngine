#pragma once
#include "Runtime/Attribute.h"
#include "Runtime/Datum.h"
#include "WorldState.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		/**
			Forward decelerations
		*/
		class Sector;

		/**
			Copy semantics for World class is deleted.
		*/
		class World final : public Runtime::Attribute
		{
			RTTI_DECLARATIONS(World, Attribute)
		public:
			
			/**
				@brief Default constructor.
			*/
			World();

			/**
				@brief Default destructor
			*/
			~World();

			/**
				Removing copy semantics
			*/
			World(const World& pOther) = delete;

			/**
				Removing copy semantics
			*/
			World& operator=(const World& pOther) = delete;

			/**
				@brief Returns the name of this sector.
				@return String that holds the name of this sector.
			*/
			std::string Name() const;

			/**
				@brief Set the name of this sector.
				@param[in] pName The name to set for this sector.
			*/
			void SetName(const std::string& pName);

			/**
				@brief Give all the sectors inside this world;
				@return Reference to datum that stores the contained sectors in the world.
			*/
			Runtime::Datum& Sectors();

			/**
				@brief Return a reference to datum that contains all the actions that his entity has.
				@return Reference to datum
			*/
			Runtime::Datum& Actions();

			/**
				@brief Create an sector of type and child it to this world.
				@param[in] pSectorName The name to be assigned to the sector.
				@return Reference to the new sector that is created.
			*/
			Sector& CreateSector(const std::string& pSectorName);

			/**
				@brief Create a new action, adopt it into this world and return the reference to the action that is created.
				@param[in] pActionType Type of action that needs to be created. This is usually the class name of the action.
				@param[in] pActionName The name to be assigned to the action.
				@return Reference to action that is created.
			*/
			Action& CreateAction(const std::string& pActionType, const std::string& pActionName);

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			void Update(WorldState& pWorldState);

			/**
				@brief Populate all the prescribed attributes of world.
			*/
			void Populate();
		private:
			/**
				Holds the name of this world.
			*/
			std::string mName;
		};
	}
}