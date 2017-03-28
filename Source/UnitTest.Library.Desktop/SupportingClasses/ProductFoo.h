#pragma once
#include "Runtime/RTTI.h"
#include "Generic/Factory.h"

namespace SupportingClasses
{
	class ProductFoo : public NoobEngine::Runtime::RTTI
	{
		RTTI_DECLARATIONS(ProductFoo, RTTI)
	public:
		ProductFoo();
		~ProductFoo();

	private:
		int mData;
	};

	ConcreteFactory(NoobEngine::Runtime::RTTI, ProductFoo)
}