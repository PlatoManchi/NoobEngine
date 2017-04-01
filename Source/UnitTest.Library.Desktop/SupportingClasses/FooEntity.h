#pragma once
#include "GamePlay/Entity.h"

namespace SupportingClasses
{
	class FooEntity : public NoobEngine::GamePlay::Entity
	{
		RTTI_DECLARATIONS(FooEntity, Entity)

	public:
		FooEntity();

		void Populate();

		virtual std::string ToString() const override
		{
			return "FooEntity";
		}
	};

	ConcreteFactory(NoobEngine::GamePlay::Entity, FooEntity)
}