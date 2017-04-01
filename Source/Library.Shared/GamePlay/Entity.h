#pragma once

#include "Runtime/Attribute.h"
#include "WorldState.h"
#include "Generic/Factory.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		/**
			Forward declaring sector
		*/
		class Sector;
		
		/**
			Copy semantics for entity is removed.
		*/
		class Entity : public Runtime::Attribute
		{
			RTTI_DECLARATIONS(Entity, Attribute)
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
				Removing copy semantics for Entity.
			*/
			Entity(const Entity& pOther) = delete;

			/**
				Removing copy semantics for Entity.
			*/
			Entity& operator=(const Entity& pOther) = delete;

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
			Sector& GetParentSector() const;

			/**
				@brief Adopt the entity into this sector.
				@param[in] Reference to the sector to adopt this entity into.
			*/
			void SetParentSector(Sector& pSector);

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			void Update(WorldState& pWorldState);

			/**
				@brief Populate all the prescribed attributes.
			*/
			void Populate();

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
#define ConcreteEntityFactory(ConcreteType)		\
		ConcreteFactory(Entity, ConcreteType)	\

		ConcreteEntityFactory(Entity)
	}
}