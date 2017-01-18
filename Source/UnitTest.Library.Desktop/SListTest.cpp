#include "pch.h"
#include "CppUnitTest.h"
#include "Container/SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(SListTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}

		// testing the default constructor
		TEST_METHOD(Constructor_Default_Test)
		{
			FIEAGameEngine::Container::SList<int32_t> list;
			uint32_t initialSize = 0;
			Assert::AreEqual(initialSize, list.Size());
		}

		// testing the copy constructor
		TEST_METHOD(Constructor_Copy_Test)
		{
			FIEAGameEngine::Container::SList<int32_t> list1;
			list1.PushBack(20);
			FIEAGameEngine::Container::SList<int32_t> list2(list1);

			Assert::AreEqual(list1.Size(), list2.Size());
			Assert::AreEqual(list1.PopFront(), list2.PopFront());
		}

		// testing equal operator
		TEST_METHOD(Operator_Assignment_Test)
		{
			FIEAGameEngine::Container::SList<int32_t> list1;
			list1.PushBack(20);
			list1.PushBack(30);
			list1.PushBack(40);
			FIEAGameEngine::Container::SList<int32_t> list2;
			list2 = list1;

			Assert::AreEqual(list1.Size(), list2.Size());
			Assert::AreEqual(list1.PopFront(), list2.PopFront());
		}

		// testing PushFront
		TEST_METHOD(Method_PushFront_Test)
		{
			int32_t data = 20;
			FIEAGameEngine::Container::SList<int32_t> list1;
			list1.PushFront(10);
			list1.PushFront(30);
			list1.PushFront(data);

			Assert::AreEqual((uint32_t)3, list1.Size());
		}

		// testing PushBack
		TEST_METHOD(Method_PushBack_Test)
		{
			int32_t data = 20;
			FIEAGameEngine::Container::SList<int32_t> list1;
			list1.PushBack(10);
			list1.PushBack(30);
			list1.PushBack(data);

			Assert::AreEqual((uint32_t)3, list1.Size());
		}

		// testing PushFront and Front function
		TEST_METHOD(Method_PushFront_Front_Test)
		{
			int32_t data = 20;
			FIEAGameEngine::Container::SList<int32_t> list1;
			list1.PushFront(10);
			list1.PushFront(30);
			list1.PushFront(data);
			
			Assert::AreEqual(data, list1.Front());
		}

		// testing PushBack and Back function
		TEST_METHOD(Method_PushBack_Back_Test)
		{
			int32_t data = 20;
			FIEAGameEngine::Container::SList<int32_t> list1;
			list1.PushBack(10);
			list1.PushBack(30);
			list1.PushBack(data);
			
			Assert::AreEqual(data, list1.Back());
		}

		// testing PopFront function
		TEST_METHOD(Method_PopFront_Test)
		{
			FIEAGameEngine::Container::SList<int32_t> list1;
			
			int32_t data = 10;
			list1.PushFront(data);
			int32_t d = list1.PopFront();

			Assert::AreEqual(data, d);
		}

		// testing exception case for PopFront function
		// calling PopFront on empty list
		TEST_METHOD(Method_PopFront_Exception_Test)
		{
			FIEAGameEngine::Container::SList<int32_t> list1;
			Assert::ExpectException<exception>([&] { list1.PopFront(); });
		}

		// testing exception case for Front function
		// calling Front on empty list
		TEST_METHOD(Method_Front_Exception_Test)
		{
			FIEAGameEngine::Container::SList<int32_t> list1;
			Assert::ExpectException<exception>([&] { list1.Front(); });
		}

		// testing exception case for Back function
		// calling Back on empty list
		TEST_METHOD(Method_Back_Exception_Test)
		{
			FIEAGameEngine::Container::SList<int32_t> list1;
			Assert::ExpectException<exception>([&] { list1.Back(); });
		}

		// testing size method
		TEST_METHOD(Method_Size_Test)
		{
			FIEAGameEngine::Container::SList<int32_t> list1;

			uint32_t size = 0;
			Assert::AreEqual(size, list1.Size());

			list1.PushBack(10);
			list1.PushBack(20);

			size = 2;
			Assert::AreEqual(size, list1.Size());
		}

		// testing clear method
		TEST_METHOD(Method_Clear_Test)
		{
			FIEAGameEngine::Container::SList<int32_t> list1;

			// saving memory state
			_CrtMemState clearTest_StartMemState;
			_CrtMemCheckpoint(&clearTest_StartMemState);

			// push some data
			list1.PushBack(10);
			list1.PushBack(20);

			list1.Clear();

			Assert::AreEqual((uint32_t)0, list1.Size());
			
			_CrtMemState clearTest_EndMemState;
			_CrtMemCheckpoint(&clearTest_EndMemState);

			_CrtMemState diffMemState;
			if (_CrtMemDifference(&diffMemState, &clearTest_StartMemState, &clearTest_EndMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}
		private:
			static _CrtMemState sStartMemState;
	   };

	   _CrtMemState SListTest::sStartMemState;

}