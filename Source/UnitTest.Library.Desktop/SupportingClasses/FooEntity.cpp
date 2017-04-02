#include "pch.h"
#include "FooEntity.h"

namespace SupportingClasses
{
	RTTI_DEFINITIONS(FooEntity)

	FooEntity::FooEntity() :
		Entity()
	{
		Populate();
	}

	void FooEntity::Populate()
	{
		Entity::Populate();
	}

	void FooEntity::Update(NoobEngine::GamePlay::WorldState& pWorldState)
	{
		Entity::Update(pWorldState);

		// increment the life count
		int lifeCount = (operator[]("Life")).Get<int>();
		(operator[]("Life")).Set(lifeCount + 1);
	}
}