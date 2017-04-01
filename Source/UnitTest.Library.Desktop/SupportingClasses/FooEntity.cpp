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
}