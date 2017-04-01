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

		class World : public Runtime::Attribute
		{
			RTTI_DECLARATIONS(World, Attribute)
		public:
			/**
				Holds the key where all the sectors are stored.
			*/
			static const char* sSectorsKey;

			/**
				@brief Default constructor.
			*/
			World();

			/**
				@brief Default destructor
			*/
			~World();

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
				@brief Create an sector of type and child it to this world.
				@param[in] pSectorName The name to be assigned to the sector.
				@return Reference to the new sector that is created.
			*/
			Sector& CreateSector(const std::string& pSectorName);

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			void Update(WorldState& pWorldState);

		private:
			/**
				Holds the name of this world.
			*/
			std::string mName;
		};
	}
}