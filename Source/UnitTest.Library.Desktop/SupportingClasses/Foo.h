#pragma once

namespace SupportingClasses
{
	class Foo
	{
		int32_t* mData;
		static int32_t ID;
	public:
		int32_t mID;

		Foo();
		explicit Foo(int32_t pData);
		Foo(const Foo& pFooObj);
		~Foo();

		Foo& operator=(const Foo& rhs);
		bool operator==(const Foo& rhs) const;
	};
}

