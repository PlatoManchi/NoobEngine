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
		class Entity;
		class World;
		
		class Sector : public Runtime::Attribute
		{
			RTTI_DECLARATIONS(Sector, Attribute)
		public:
			/**
				Holds the key where all the sectors are stored.
			*/
			static const char* sEntitiesKey;

			/**
				@brief Default constructor.
			*/
			Sector();

			/**
				@brief Default destructor.
			*/
			~Sector();

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
				@brief Give all the entities inside this sector;
				@return Reference to datum that stores the contained entities in the sector.
			*/
			Runtime::Datum& Entities();

			/**
				@brief Create an entity of type and child it to this sector.
				@param[in] pEntityType Type of entity that needs to be created. This is usually the class name of the entity.
				@param[in] pEntityName The name to be assigned to the entity.
				@return Reference to the new entity that is created.
			*/
			Entity& CreateEntity(const std::string& pEntityType, const std::string& pEntityName);

			/**
				@brief Get the world that this sector is adopted to.
				@return Reference to world.
			*/
			World& GetParentWorld() const;

			/**
				@brief Set the world for this sector.
				@param[in] Reference to the world this sector has to be adopted into.
			*/
			void SetParentWorld(World& pWorld);

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			void Update(WorldState& pWorldState);
		private:
			/**
				Holds the name of this sector.
			*/
			std::string mName;

			/**
				Holds the pointer to parent world.
			*/
			World* mParent;

			
		};
	}
}