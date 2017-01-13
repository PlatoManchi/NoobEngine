#include "pch.h"
#include "CppUnitTest.h"
#include "Container/SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(SListTest)
	{
	public:
		
		// testing the default constructor
		TEST_METHOD(ConstructorDefaultTest)
		{
			FIEAGameEngine::Container::SList list;

			Assert::AreEqual(0, list.GetData());
		}

		// testing the parameterized constructor
		TEST_METHOD(ConstructorParameterizedTest)
		{
			int32_t data = 10;
			FIEAGameEngine::Container::SList list(data);

			Assert::AreEqual(data, list.GetData());
		}

		// should i test GetData? its been called in previous tests
	};
}