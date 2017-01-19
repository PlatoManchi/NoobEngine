#include "pch.h"
#include "Foo.h"

namespace SupportingClasses
{
	Foo::Foo() : mData(nullptr)
	{}

	Foo::Foo(int32_t pData)
	{
		mData = new int32_t(pData);
	}

	Foo::Foo(const Foo & pFooObj)
	{
		mData = new int32_t(*pFooObj.mData);
	}

	Foo::~Foo()
	{
		if (mData)
		{
			delete(mData);
		}
	}
	Foo& Foo::operator=(const Foo& rhs)
	{
		if (this != &rhs)
		{
			*mData = *rhs.mData;
		}
		return *this;
	}
	bool Foo::operator==(const Foo & rhs)
	{
		return (mData != nullptr) && 
				(rhs.mData != nullptr) &&
				(*mData == *rhs.mData);
	}
}