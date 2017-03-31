#pragma once

#include "Runtime/Attribute.h"
#include "WorldState.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		/**
			Forward declaring sector
		*/
		class Sector;
		
		class Entity : public Runtime::Attribute
		{
		public:
			/**
				@brief Default constructor
			*/
			Entity();

			/**
				@brief Default destructor
			*/
			~Entity();

			/**
				@brief Returns the name of the entity.
				@return String that represents the name of the entity.
			*/
			std::string Name() const;

			/**
				@brief Set the name of the entity.
				@param[in] pName Constant reference to the string that needs to be set as name for this entity.
			*/
			void SetName(const std::string& pName);

			/**
				@brief Get the sector that this entity belongs to or attached to.
				@return Reference to the sector that this entity belongs to.
			*/
			Sector& GetSector() const;

			/**
				@brief Adopt the entity into this sector.
				@param[in] Reference to the sector to adopt this entity into.
			*/
			void SetSector(const Sector& pSector);

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			void Update(WorldState& pWorldState);
		private:
			/**
				Name of the entity
			*/
			std::string mName;

			/**
				The parent sector that this entity belongs to.
			*/
			Sector* mParent;
		};
	}
}