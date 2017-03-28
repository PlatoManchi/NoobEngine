#include "pch.h"
#include "FactoryFooFactoryT.h"

namespace SupportingClasses
{
	FactoryFooFactoryT::FactoryFooFactoryT()
	{
		Add(*this);
	}

	FactoryFooFactoryT::~FactoryFooFactoryT()
	{
		Remove(ClassName());
	}

	std::string FactoryFooFactoryT::ClassName() const
	{ 
		return "FactoryFoo"; 
	}

	NoobEngine::Runtime::RTTI* FactoryFooFactoryT::Create() const
	{
		NoobEngine::Runtime::RTTI* product = new ProductFoo();
		return product;
	}
}