#pragma once
#include "IProduct.h"
#include "Generic/Factory.h"

namespace SupportingClasses
{
	class NonRTTIProduct : public IProduct
	{
	public:
		virtual void AbstractFunction() override;
	};

	ConcreteFactory(IProduct, NonRTTIProduct)
}