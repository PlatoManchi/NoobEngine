#pragma once

#include "Runtime/Attribute.h"
#include "WorldState.h"
#include "Generic/Factory.h"
#include "Action.h"

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
			virtual ~Entity();

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
				@brief Return a reference to datum that contains all the actions that his entity has.
				@return Reference to datum
			*/
			Runtime::Datum& Actions();

			/**
				@brief Create a new action, adopt it into this entity and return the reference to the action that is created.
				@return Reference to action that is created.
			*/
			Action& CreateAction(const std::string& pActionType, const std::string& pActionName);

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
			virtual void Update(WorldState& pWorldState);

			/**
				@brief Populate all the prescribed attributes.
			*/
			void Populate();

			virtual std::string ToString() const override
			{
				return "Entity";
			}

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