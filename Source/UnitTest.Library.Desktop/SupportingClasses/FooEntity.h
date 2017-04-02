#pragma once
#include "GamePlay/Entity.h"
#include "GamePlay/WorldState.h"

namespace SupportingClasses
{
	class FooEntity : public NoobEngine::GamePlay::Entity
	{
		RTTI_DECLARATIONS(FooEntity, Entity)

	public:
		FooEntity();

		void Populate();
		/**
			@brief Called every frame.
			@param[in] pWorldState Reference to the world state of current game.
		*/
		virtual void Update(NoobEngine::GamePlay::WorldState& pWorldState) override;

		virtual std::string ToString() const override
		{
			return "FooEntity";
		}
	};

	ConcreteFactory(NoobEngine::GamePlay::Entity, FooEntity)
}