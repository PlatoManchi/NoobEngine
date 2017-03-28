#pragma once

#include "Generic/Factory.h"
#include "Runtime/RTTI.h"
#include "ProductFoo.h"

using namespace NoobEngine::Generic;

namespace SupportingClasses
{
	class FactoryFooFactoryT : public Factory<NoobEngine::Runtime::RTTI>
	{
	public:
		FactoryFooFactoryT();
		~FactoryFooFactoryT();

		virtual std::string ClassName() const override;

		virtual NoobEngine::Runtime::RTTI* Create() const override;
	};
}

