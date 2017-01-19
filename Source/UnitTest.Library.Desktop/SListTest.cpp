#include "pch.h"
#include "CppUnitTest.h"
#include "Container/SList.h"
#include "SupportingClasses/Foo.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SupportingClasses;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			// adding helper function to namespace for assert to compare two foo objects and pointers
			template<> inline std::wstring ToString<Foo>(const Foo*)
			{
				return L"Foo";
			}

			template<> inline std::wstring ToString<Foo>(Foo*)
			{
				return L"Foo";
			}

			template<> inline std::wstring ToString<Foo>(const Foo&)
			{
				return L"Foo";
			}

		}
	}
}

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
			endMemState;
			diffMemState;
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
			//------------------------- int32_t----------------------------
			FIEAGameEngine::Container::SList<int32_t> listInt;
			uint32_t initialSize = 0;
			Assert::AreEqual(initialSize, listInt.Size());

			//-----------------------int32_t pointer----------------------
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr;
			Assert::AreEqual(initialSize, listIntPtr.Size());

			//------------------------Foo pointer-------------------------
			FIEAGameEngine::Container::SList<Foo*> listFoo;
			Assert::AreEqual(initialSize, listFoo.Size());
		}

		// testing the copy constructor
		TEST_METHOD(Constructor_Copy_Test)
		{
			//------------------------- int32_t----------------------------
			FIEAGameEngine::Container::SList<int32_t> listInt1;
			listInt1.PushBack(20);
			FIEAGameEngine::Container::SList<int32_t> listInt2(listInt1);

			Assert::AreEqual(listInt1.Size(), listInt2.Size());
			Assert::AreEqual(listInt1.PopFront(), listInt2.PopFront());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;
			listIntPtr1.PushBack(intPtr1);
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr2(listIntPtr1);

			Assert::AreEqual(listIntPtr1.Size(), listIntPtr2.Size());
			Assert::AreEqual(listIntPtr1.PopFront(), listIntPtr2.PopFront());
			// free memory used by data
			delete(intPtr1);

			//------------------------Foo pointer-------------------------
			Foo* fooPtr1 = new Foo();
			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			FIEAGameEngine::Container::SList<Foo*> listFooPtr2(listFooPtr1);
			
			Assert::AreEqual(listFooPtr1.Size(), listFooPtr2.Size());
			Assert::AreEqual(listFooPtr1.PopFront(), listFooPtr2.PopFront());
			// free memory used by data
			delete(fooPtr1);
		}

		// testing equal operator
		TEST_METHOD(Operator_Assignment_Test)
		{
			//------------------------- int32_t----------------------------
			FIEAGameEngine::Container::SList<int32_t> listInt1;
			listInt1.PushBack(20);
			listInt1.PushBack(30);
			listInt1.PushBack(40);
			FIEAGameEngine::Container::SList<int32_t> listInt2;
			listInt2 = listInt1;

			Assert::AreEqual(listInt1.Size(), listInt2.Size());
			Assert::AreEqual(listInt1.PopFront(), listInt2.PopFront());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;
			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);
			listIntPtr1.PushBack(intPtr3);
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr2;
			listIntPtr2 = listIntPtr1;

			Assert::AreEqual(listIntPtr1.Size(), listIntPtr2.Size());
			Assert::AreEqual(listIntPtr1.PopFront(), listIntPtr2.PopFront());
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo* fooPtr1 = new Foo();
			Foo* fooPtr2 = new Foo();
			Foo* fooPtr3 = new Foo();

			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);
			listFooPtr1.PushBack(fooPtr3);
			FIEAGameEngine::Container::SList<Foo*> listFooPtr2;
			listFooPtr2 = listFooPtr1;

			Assert::AreEqual(listFooPtr1.Size(), listFooPtr2.Size());
			Assert::AreEqual(listFooPtr1.PopFront(), listFooPtr2.PopFront());
			// freeing memory
			delete(fooPtr1);
			delete(fooPtr2);
			delete(fooPtr3);
		}

		// testing PushFront
		TEST_METHOD(Method_PushFront_Test)
		{
			//------------------------- int32_t----------------------------
			int32_t data = 20;
			FIEAGameEngine::Container::SList<int32_t> listInt1;
			listInt1.PushFront(10);
			listInt1.PushFront(30);
			listInt1.PushFront(data);

			Assert::AreEqual((uint32_t)3, listInt1.Size());


			//-----------------------int32_t pointer----------------------
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			listIntPtr1.PushFront(intPtr1);
			listIntPtr1.PushFront(intPtr2);
			listIntPtr1.PushFront(intPtr3);

			Assert::AreEqual((uint32_t)3, listIntPtr1.Size());
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;
			Foo* fooPtr1 = new Foo;
			Foo* fooPtr2 = new Foo;
			Foo* fooPtr3 = new Foo;

			listFooPtr1.PushFront(fooPtr1);
			listFooPtr1.PushFront(fooPtr2);
			listFooPtr1.PushFront(fooPtr3);

			Assert::AreEqual((uint32_t)3, listFooPtr1.Size());
			// freeing memory
			delete(fooPtr1);
			delete(fooPtr2);
			delete(fooPtr3);
		}

		// testing PushBack
		TEST_METHOD(Method_PushBack_Test)
		{
			//------------------------- int32_t----------------------------
			int32_t data = 20;
			FIEAGameEngine::Container::SList<int32_t> list1;
			list1.PushBack(10);
			list1.PushBack(30);
			list1.PushBack(data);

			Assert::AreEqual((uint32_t)3, list1.Size());

			//-----------------------int32_t pointer----------------------
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);
			listIntPtr1.PushBack(intPtr3);

			Assert::AreEqual((uint32_t)3, listIntPtr1.Size());
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;
			Foo* fooPtr1 = new Foo;
			Foo* fooPtr2 = new Foo;
			Foo* fooPtr3 = new Foo;

			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);
			listFooPtr1.PushBack(fooPtr3);

			Assert::AreEqual((uint32_t)3, listFooPtr1.Size());
			// freeing memory
			delete(fooPtr1);
			delete(fooPtr2);
			delete(fooPtr3);
		}

		// testing PushFront and Front function
		TEST_METHOD(Method_PushFront_Front_Test)
		{
			//------------------------- int32_t----------------------------
			int32_t data = 20;
			FIEAGameEngine::Container::SList<int32_t> list1;
			list1.PushFront(10);
			list1.PushFront(30);
			list1.PushFront(data);
			
			Assert::AreEqual(data, list1.Front());

			//-----------------------int32_t pointer----------------------
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			listIntPtr1.PushFront(intPtr1);
			listIntPtr1.PushFront(intPtr2);
			listIntPtr1.PushFront(intPtr3);

			Assert::AreEqual(intPtr3, listIntPtr1.Front());
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;
			Foo* fooPtr1 = new Foo;
			Foo* fooPtr2 = new Foo;
			Foo* fooPtr3 = new Foo;

			listFooPtr1.PushFront(fooPtr1);
			listFooPtr1.PushFront(fooPtr2);
			listFooPtr1.PushFront(fooPtr3);

			Assert::AreEqual(fooPtr3, listFooPtr1.Front());
			// freeing memory
			delete(fooPtr1);
			delete(fooPtr2);
			delete(fooPtr3);
		}

		// testing PushBack and Back function
		TEST_METHOD(Method_PushBack_Back_Test)
		{
			//------------------------- int32_t----------------------------
			int32_t data = 20;
			FIEAGameEngine::Container::SList<int32_t> list1;
			list1.PushBack(10);
			list1.PushBack(30);
			list1.PushBack(data);
			
			Assert::AreEqual(data, list1.Back());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;
			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);
			listIntPtr1.PushBack(intPtr3);
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr2;
			listIntPtr2 = listIntPtr1;

			Assert::AreEqual(intPtr3, listIntPtr2.Back());
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo* fooPtr1 = new Foo();
			Foo* fooPtr2 = new Foo();
			Foo* fooPtr3 = new Foo();

			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);
			listFooPtr1.PushBack(fooPtr3);
			FIEAGameEngine::Container::SList<Foo*> listFooPtr2;
			listFooPtr2 = listFooPtr1;

			Assert::AreEqual(fooPtr3, listFooPtr2.Back());
			// freeing memory
			delete(fooPtr1);
			delete(fooPtr2);
			delete(fooPtr3);
		}

		// testing PopFront function
		TEST_METHOD(Method_PopFront_Test)
		{
			//------------------------- int32_t----------------------------
			FIEAGameEngine::Container::SList<int32_t> list1;
			
			int32_t data = 10;
			list1.PushBack(data);
			
			Assert::AreEqual(data, list1.PopFront());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;
			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);
			listIntPtr1.PushBack(intPtr3);
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr2;
			listIntPtr2 = listIntPtr1;

			Assert::AreEqual(intPtr1, listIntPtr2.PopFront());
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo* fooPtr1 = new Foo();
			Foo* fooPtr2 = new Foo();
			Foo* fooPtr3 = new Foo();

			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);
			listFooPtr1.PushBack(fooPtr3);
			FIEAGameEngine::Container::SList<Foo*> listFooPtr2;
			listFooPtr2 = listFooPtr1;

			Assert::AreEqual(fooPtr1, listFooPtr2.PopFront());
			// freeing memory
			delete(fooPtr1);
			delete(fooPtr2);
			delete(fooPtr3);
		}

		// testing exception case for PopFront function
		// calling PopFront on empty list
		TEST_METHOD(Method_PopFront_Exception_Test)
		{
			//------------------------- int32_t----------------------------
			FIEAGameEngine::Container::SList<int32_t> listInt1;
			Assert::ExpectException<exception>([&] { listInt1.PopFront(); });

			//-----------------------int32_t pointer----------------------
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;
			Assert::ExpectException<exception>([&] { listIntPtr1.PopFront(); });

			//------------------------Foo pointer-------------------------
			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;
			Assert::ExpectException<exception>([&] { listFooPtr1.PopFront(); });
		}

		// testing exception case for Front function
		// calling Front on empty list
		TEST_METHOD(Method_Front_Exception_Test)
		{
			//------------------------- int32_t----------------------------
			FIEAGameEngine::Container::SList<int32_t> list1;
			Assert::ExpectException<exception>([&] { list1.Front(); });

			//-----------------------int32_t pointer----------------------
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;
			Assert::ExpectException<exception>([&] { listIntPtr1.Front(); });

			//------------------------Foo pointer-------------------------
			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;
			Assert::ExpectException<exception>([&] { listFooPtr1.Front(); });
		}

		// testing exception case for Back function
		// calling Back on empty list
		TEST_METHOD(Method_Back_Exception_Test)
		{
			//------------------------- int32_t----------------------------
			FIEAGameEngine::Container::SList<int32_t> list1;
			Assert::ExpectException<exception>([&] { list1.Back(); });

			//-----------------------int32_t pointer----------------------
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;
			Assert::ExpectException<exception>([&] { listIntPtr1.Back(); });

			//------------------------Foo pointer-------------------------
			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;
			Assert::ExpectException<exception>([&] { listFooPtr1.Back(); });
		}

		// testing size method
		TEST_METHOD(Method_Size_Test)
		{
			//------------------------- int32_t----------------------------
			FIEAGameEngine::Container::SList<int32_t> listInt1;

			uint32_t size = 0;
			Assert::AreEqual(size, listInt1.Size());

			listInt1.PushBack(10);
			listInt1.PushBack(20);

			size = 2;
			Assert::AreEqual(size, listInt1.Size());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;

			size = 0;
			Assert::AreEqual(size, listIntPtr1.Size());

			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);

			size = 2;
			Assert::AreEqual(size, listIntPtr1.Size());
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);

			//------------------------Foo pointer-------------------------
			Foo* fooPtr1 = new Foo;
			Foo* fooPtr2 = new Foo;
			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;

			size = 0;
			Assert::AreEqual(size, listFooPtr1.Size());

			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);

			size = 2;
			Assert::AreEqual(size, listFooPtr1.Size());
			// freeing memory
			delete(fooPtr1);
			delete(fooPtr2);
		}

		// testing clear method
		TEST_METHOD(Method_Clear_Test)
		{
			//------------------------- int32_t----------------------------
			// saving memory state
			_CrtMemState clearTest_StartMemState;
			clearTest_StartMemState;
			_CrtMemCheckpoint(&clearTest_StartMemState);

			FIEAGameEngine::Container::SList<int32_t> listInt1;

			// push some data
			listInt1.PushBack(10);
			listInt1.PushBack(20);

			listInt1.Clear();

			Assert::AreEqual((uint32_t)0, listInt1.Size());
			
			_CrtMemState clearTest_EndMemState;
			clearTest_EndMemState;
			_CrtMemCheckpoint(&clearTest_EndMemState);

			_CrtMemState diffMemState;
			diffMemState;
			if (_CrtMemDifference(&diffMemState, &clearTest_StartMemState, &clearTest_EndMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}

			//-----------------------int32_t pointer----------------------
			// saving memory state
			_CrtMemCheckpoint(&clearTest_StartMemState);

			FIEAGameEngine::Container::SList<int32_t*> listIntPtr1;

			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);

			// push some data
			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);

			listIntPtr1.Clear();

			Assert::AreEqual((uint32_t)0, listIntPtr1.Size());

			// freeing memory
			delete(intPtr1);
			delete(intPtr2);

			_CrtMemCheckpoint(&clearTest_EndMemState);

			if (_CrtMemDifference(&diffMemState, &clearTest_StartMemState, &clearTest_EndMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}

			//------------------------Foo pointer-------------------------
			// saving memory state
			_CrtMemCheckpoint(&clearTest_StartMemState);

			FIEAGameEngine::Container::SList<Foo*> listFooPtr1;

			Foo* fooPtr1 = new Foo;
			Foo* fooPtr2 = new Foo;
			// push some data
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);

			listFooPtr1.Clear();

			Assert::AreEqual((uint32_t)0, listFooPtr1.Size());

			// freeing memory
			delete(fooPtr1);
			delete(fooPtr2);

			_CrtMemCheckpoint(&clearTest_EndMemState);

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