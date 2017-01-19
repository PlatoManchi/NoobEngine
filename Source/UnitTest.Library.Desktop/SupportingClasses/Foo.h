#pragma once

namespace SupportingClasses
{
	class Foo
	{
		int32_t* mData;
	public:
		Foo();
		Foo(int32_t pData);
		Foo(const Foo& pFooObj);
		~Foo();

		Foo& operator=(const Foo& rhs);
		bool operator==(const Foo& rhs);
	};
}

