#include "pch.h"
#include "Foo.h"

namespace SupportingClasses
{
	int32_t Foo::ID = 0;
	Foo::Foo() : mData(nullptr)
	{
		ID++;
		mID = ID;
	}

	Foo::Foo(int32_t pData)
	{
		ID++;
		mID = ID;
		mData = new int32_t(pData);
	}

	Foo::Foo(const Foo& pFooObj)
	{
		ID++;
		mID = ID;
		if (pFooObj.mData)
		{
			mData = new int32_t(*pFooObj.mData);
		}
		else
		{
			mData = nullptr;
		}
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
		this->mID = rhs.mID;
		if (this != &rhs)
		{
			if (rhs.mData)
			{
				// if rhs has data
				if (mData)
				{
					*mData = *rhs.mData;
				}
				else
				{
					mData = new int32_t(*rhs.mData);
				}
			}
			else
			{
				// if rhs has no data
				if (mData)
				{
					delete (mData);
				}

				mData = nullptr;
			}
		}
		return *this;
	}
	bool Foo::operator==(const Foo & rhs) const
	{
		return (mData == rhs.mData) || 
				((mData != nullptr) && (rhs.mData != nullptr) && (*mData == *rhs.mData));
	}
}