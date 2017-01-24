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
			

			template<> inline std::wstring ToString<Foo>(const Foo& t)
			{
				std::wstringstream stringStream;
				stringStream << "Foo_" << (t.mID);
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<NoobEngine::Container::SList<int32_t>::Iterator>(typename const NoobEngine::Container::SList<int32_t>::Iterator& )
			{
				std::wstringstream stringStream;
				stringStream << "Int Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<NoobEngine::Container::SList<int32_t*>::Iterator>(typename const NoobEngine::Container::SList<int32_t*>::Iterator& )
			{
				std::wstringstream stringStream;
				stringStream << "Int* Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<NoobEngine::Container::SList<Foo>::Iterator>(typename const NoobEngine::Container::SList<Foo>::Iterator& )
			{
				std::wstringstream stringStream;
				stringStream << "Foo Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
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
			NoobEngine::Container::SList<int32_t> listInt;
			uint32_t initialSize = 0;
			Assert::AreEqual(initialSize, listInt.Size());

			//-----------------------int32_t pointer----------------------
			NoobEngine::Container::SList<int32_t*> listIntPtr;
			Assert::AreEqual(initialSize, listIntPtr.Size());

			//------------------------Foo pointer-------------------------
			NoobEngine::Container::SList<Foo*> listFoo;
			Assert::AreEqual(initialSize, listFoo.Size());
		}

		// testing the copy constructor
		TEST_METHOD(Constructor_Copy_Test)
		{
			//------------------------- int32_t----------------------------
			NoobEngine::Container::SList<int32_t> listInt1;
			listInt1.PushBack(20);
			NoobEngine::Container::SList<int32_t> listInt2(listInt1);

			Assert::AreEqual(listInt1.Size(), listInt2.Size());
			Assert::AreEqual(listInt1.PopFront(), listInt2.PopFront());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			NoobEngine::Container::SList<int32_t*> listIntPtr1;
			listIntPtr1.PushBack(intPtr1);
			NoobEngine::Container::SList<int32_t*> listIntPtr2(listIntPtr1);

			Assert::AreEqual(listIntPtr1.Size(), listIntPtr2.Size());
			Assert::AreEqual(listIntPtr1.PopFront(), listIntPtr2.PopFront());
			// free memory used by data
			delete(intPtr1);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1;
			NoobEngine::Container::SList<Foo> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			NoobEngine::Container::SList<Foo> listFooPtr2(listFooPtr1);
			
			Assert::AreEqual(listFooPtr1.Size(), listFooPtr2.Size());
			Assert::AreEqual(listFooPtr1.PopFront(), listFooPtr2.PopFront());
		}

		// testing equal operator
		TEST_METHOD(Operator_Assignment_Test)
		{
			//------------------------- int32_t----------------------------
			NoobEngine::Container::SList<int32_t> listInt1;
			listInt1.PushBack(20);
			listInt1.PushBack(30);
			listInt1.PushBack(40);
			NoobEngine::Container::SList<int32_t> listInt2;
			listInt2 = listInt1;

			Assert::AreEqual(listInt1.Size(), listInt2.Size());
			Assert::AreEqual(listInt1.PopFront(), listInt2.PopFront());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			NoobEngine::Container::SList<int32_t*> listIntPtr1;
			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);
			listIntPtr1.PushBack(intPtr3);
			NoobEngine::Container::SList<int32_t*> listIntPtr2;
			listIntPtr2 = listIntPtr1;

			Assert::AreEqual(listIntPtr1.Size(), listIntPtr2.Size());
			Assert::AreEqual(listIntPtr1.PopFront(), listIntPtr2.PopFront());
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1(10);
			Foo fooPtr2;
			Foo fooPtr3;

			NoobEngine::Container::SList<Foo> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);
			listFooPtr1.PushBack(fooPtr3);
			NoobEngine::Container::SList<Foo> listFooPtr2;
			listFooPtr2 = listFooPtr1;

			Assert::AreEqual(listFooPtr1.Size(), listFooPtr2.Size());
			Assert::AreEqual(listFooPtr1.PopFront(), listFooPtr2.PopFront());
		}

		// testing PushFront
		TEST_METHOD(Method_PushFront_Test)
		{
			//------------------------- int32_t----------------------------
			int32_t data = 20;
			NoobEngine::Container::SList<int32_t> listInt1;
			
			Assert::AreEqual((uint32_t)0, listInt1.Size());

			listInt1.PushFront(data);

			Assert::AreEqual((uint32_t)1, listInt1.Size());
			Assert::AreEqual(data, listInt1.Front());

			//-----------------------int32_t pointer----------------------
			NoobEngine::Container::SList<int32_t*> listIntPtr1;
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			Assert::AreEqual((uint32_t)0, listIntPtr1.Size());

			listIntPtr1.PushFront(intPtr1);
			listIntPtr1.PushFront(intPtr2);
			listIntPtr1.PushFront(intPtr3);

			Assert::AreEqual((uint32_t)3, listIntPtr1.Size());
			Assert::AreEqual(intPtr3, listIntPtr1.Front());

			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			NoobEngine::Container::SList<Foo> listFooPtr1;
			Foo fooPtr1;
			Foo fooPtr2;
			Foo fooPtr3;

			Assert::AreEqual((uint32_t)0, listFooPtr1.Size());

			listFooPtr1.PushFront(fooPtr1);
			listFooPtr1.PushFront(fooPtr2);
			listFooPtr1.PushFront(fooPtr3);

			Assert::AreEqual((uint32_t)3, listFooPtr1.Size());
			Assert::AreEqual(fooPtr3, listFooPtr1.Front());
		}

		// testing PushBack
		TEST_METHOD(Method_PushBack_Test)
		{
			//------------------------- int32_t----------------------------
			int32_t data = 20;
			NoobEngine::Container::SList<int32_t> list1;

			Assert::AreEqual((uint32_t)0, list1.Size());

			list1.PushBack(data);

			Assert::AreEqual((uint32_t)1, list1.Size());
			Assert::AreEqual(data, list1.Back());

			//-----------------------int32_t pointer----------------------
			NoobEngine::Container::SList<int32_t*> listIntPtr1;
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			Assert::AreEqual((uint32_t)0, listIntPtr1.Size());

			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);
			listIntPtr1.PushBack(intPtr3);

			Assert::AreEqual((uint32_t)3, listIntPtr1.Size());
			Assert::AreEqual(intPtr3, listIntPtr1.Back());

			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			NoobEngine::Container::SList<Foo> listFooPtr1;
			Foo fooPtr1;
			Foo fooPtr2;
			Foo fooPtr3;

			Assert::AreEqual((uint32_t)0, listFooPtr1.Size());

			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);
			listFooPtr1.PushBack(fooPtr3);

			Assert::AreEqual((uint32_t)3, listFooPtr1.Size());
			Assert::AreEqual(fooPtr3, listFooPtr1.Back());
		}

		// testing PushFront and Front function
		TEST_METHOD(Method_PushFront_Front_Test)
		{
			//------------------------- int32_t----------------------------
			int32_t data = 20;
			NoobEngine::Container::SList<int32_t> list1;
			list1.PushFront(data);
			
			Assert::AreEqual(data, list1.Front());

			//-----------------------int32_t pointer----------------------
			NoobEngine::Container::SList<int32_t*> listIntPtr1;
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
			NoobEngine::Container::SList<Foo> listFooPtr1;
			Foo fooPtr1;
			Foo fooPtr2;
			Foo fooPtr3;

			listFooPtr1.PushFront(fooPtr1);
			listFooPtr1.PushFront(fooPtr2);
			listFooPtr1.PushFront(fooPtr3);

			Assert::AreEqual(fooPtr3, listFooPtr1.Front());
		}

		// testing PushBack and Back function
		TEST_METHOD(Method_PushBack_Back_Test)
		{
			//------------------------- int32_t----------------------------
			int32_t data = 20;
			NoobEngine::Container::SList<int32_t> list1;
			list1.PushBack(10);
			list1.PushBack(30);
			list1.PushBack(data);
			
			Assert::AreEqual(data, list1.Back());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			NoobEngine::Container::SList<int32_t*> listIntPtr1;
			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);
			listIntPtr1.PushBack(intPtr3);
			NoobEngine::Container::SList<int32_t*> listIntPtr2;
			listIntPtr2 = listIntPtr1;

			Assert::AreEqual(intPtr3, listIntPtr2.Back());
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1;
			Foo fooPtr2;
			Foo fooPtr3;

			NoobEngine::Container::SList<Foo> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);
			listFooPtr1.PushBack(fooPtr3);
			NoobEngine::Container::SList<Foo> listFooPtr2;
			listFooPtr2 = listFooPtr1;

			Assert::AreEqual(fooPtr3, listFooPtr2.Back());
		}

		// testing PopFront function
		TEST_METHOD(Method_PopFront_Test)
		{
			//------------------------- int32_t ----------------------------
			NoobEngine::Container::SList<int32_t> list1;
			
			int32_t data = 10;
			list1.PushBack(data);
			
			Assert::AreEqual(data, list1.PopFront());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);

			NoobEngine::Container::SList<int32_t*> listIntPtr1;
			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);
			listIntPtr1.PushBack(intPtr3);
			NoobEngine::Container::SList<int32_t*> listIntPtr2;
			listIntPtr2 = listIntPtr1;

			Assert::AreEqual(intPtr1, listIntPtr2.PopFront());
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1(10);
			Foo fooPtr2(20);
			Foo fooPtr3(30);

			NoobEngine::Container::SList<Foo> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);
			listFooPtr1.PushBack(fooPtr3);
			NoobEngine::Container::SList<Foo> listFooPtr2;
			listFooPtr2 = listFooPtr1;

			Assert::AreEqual(fooPtr1, listFooPtr2.PopFront());
		}

		// testing exception case for PopFront function
		// calling PopFront on empty list
		TEST_METHOD(Method_PopFront_Exception_Test)
		{
			//------------------------- int32_t----------------------------
			NoobEngine::Container::SList<int32_t> listInt1;
			Assert::ExpectException<exception>([&] { listInt1.PopFront(); });

			//-----------------------int32_t pointer----------------------
			NoobEngine::Container::SList<int32_t*> listIntPtr1;
			Assert::ExpectException<exception>([&] { listIntPtr1.PopFront(); });

			//------------------------Foo pointer-------------------------
			NoobEngine::Container::SList<Foo*> listFooPtr1;
			Assert::ExpectException<exception>([&] { listFooPtr1.PopFront(); });
		}

		// testing exception case for Front function
		// calling Front on empty list
		TEST_METHOD(Method_Front_Exception_Test)
		{
			//------------------------- int32_t----------------------------
			NoobEngine::Container::SList<int32_t> list1;
			Assert::ExpectException<exception>([&] { list1.Front(); });

			//-----------------------int32_t pointer----------------------
			NoobEngine::Container::SList<int32_t*> listIntPtr1;
			Assert::ExpectException<exception>([&] { listIntPtr1.Front(); });

			//------------------------Foo pointer-------------------------
			NoobEngine::Container::SList<Foo> listFooPtr1;
			Assert::ExpectException<exception>([&] { listFooPtr1.Front(); });
		}

		// testing exception case for Back function
		// calling Back on empty list
		TEST_METHOD(Method_Back_Exception_Test)
		{
			//------------------------- int32_t----------------------------
			NoobEngine::Container::SList<int32_t> list1;
			Assert::ExpectException<exception>([&] { list1.Back(); });

			//-----------------------int32_t pointer----------------------
			NoobEngine::Container::SList<int32_t*> listIntPtr1;
			Assert::ExpectException<exception>([&] { listIntPtr1.Back(); });

			//------------------------Foo pointer-------------------------
			NoobEngine::Container::SList<Foo> listFooPtr1;
			Assert::ExpectException<exception>([&] { listFooPtr1.Back(); });
		}

		// testing size method
		TEST_METHOD(Method_Size_Test)
		{
			//------------------------- int32_t----------------------------
			NoobEngine::Container::SList<int32_t> listInt1;

			uint32_t size = 0;
			Assert::AreEqual(size, listInt1.Size());

			listInt1.PushBack(10);
			listInt1.PushBack(20);

			size = 2;
			Assert::AreEqual(size, listInt1.Size());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			NoobEngine::Container::SList<int32_t*> listIntPtr1;

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
			Foo fooPtr1(10);
			Foo fooPtr2(20);
			NoobEngine::Container::SList<Foo> listFooPtr1;

			size = 0;
			Assert::AreEqual(size, listFooPtr1.Size());

			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);

			size = 2;
			Assert::AreEqual(size, listFooPtr1.Size());
		}

		// testing clear method
		TEST_METHOD(Method_Clear_Test)
		{
			//------------------------- int32_t----------------------------
			// saving memory state
			_CrtMemState clearTest_StartMemState;
			clearTest_StartMemState;
			_CrtMemCheckpoint(&clearTest_StartMemState);

			NoobEngine::Container::SList<int32_t> listInt1;

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

			NoobEngine::Container::SList<int32_t*> listIntPtr1;

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
			Foo fooPtr1(10);
			Foo fooPtr2(20);
			//Foo fooPtr3 = 30;
			// saving memory state
			_CrtMemCheckpoint(&clearTest_StartMemState);

			NoobEngine::Container::SList<Foo> listFooPtr1;
			// push some data
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);

			listFooPtr1.Clear();

			Assert::AreEqual((uint32_t)0, listFooPtr1.Size());

			_CrtMemCheckpoint(&clearTest_EndMemState);

			if (_CrtMemDifference(&diffMemState, &clearTest_StartMemState, &clearTest_EndMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}

		TEST_METHOD(Method_Iterator_Operator_Test)
		{
			//------------------------- int32_t----------------------------
			NoobEngine::Container::SList<int32_t> listInt1;

			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;

			listInt1.PushBack(int1);
			listInt1.PushBack(int2);
			listInt1.PushBack(int3);

			NoobEngine::Container::SList<int32_t>::Iterator itr = listInt1.end();
			Assert::ExpectException<exception>([&] { ++itr;	});
			Assert::ExpectException<exception>([&] { itr++; });

			//-----------------------int32_t pointer----------------------

			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			NoobEngine::Container::SList<int32_t*> listIntPtr1;

			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);

			NoobEngine::Container::SList<int32_t*>::Iterator intPtrItr = listIntPtr1.end();
			Assert::ExpectException<exception>([&] { ++intPtrItr; });
			Assert::ExpectException<exception>([&] { intPtrItr++; });
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);

			//------------------------Foo pointer-------------------------

			Foo fooPtr1(10);
			Foo fooPtr2(20);
			NoobEngine::Container::SList<Foo> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);

			NoobEngine::Container::SList<Foo>::Iterator fooItr = listFooPtr1.end();
			Assert::ExpectException<exception>([&] { ++fooItr; });
			Assert::ExpectException<exception>([&] { fooItr++; });
		}

		TEST_METHOD(Method_Find_Test)
		{
			//------------------------- int32_t----------------------------
			NoobEngine::Container::SList<int32_t> listInt1;

			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;

			listInt1.PushBack(int1);
			listInt1.PushBack(int2);
			listInt1.PushBack(int3);

			Assert::AreEqual(int2, *(listInt1.Find(int2)));

			Assert::ExpectException<exception>([&] 
			{ 
				int32_t int4 = 100; 
				*listInt1.Find(int4); 
			});
			
			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			NoobEngine::Container::SList<int32_t*> listIntPtr1;

			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);

			Assert::AreEqual(intPtr2, *listIntPtr1.Find(intPtr2));
			
			int32_t* intPtr3 = new int32_t(30);
			Assert::ExpectException<exception>([&]
			{
				*listIntPtr1.Find(intPtr3);
			});

			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1(10);
			Foo fooPtr2(20);
			NoobEngine::Container::SList<Foo> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);

			Assert::AreEqual(fooPtr2, *listFooPtr1.Find(fooPtr2));
			Foo fooPtr3(30);
			Assert::ExpectException<exception>([&]
			{
				*listFooPtr1.Find(fooPtr3);
			});
		}

		TEST_METHOD(Method_Remove_Test)
		{
			//------------------------- int32_t----------------------------
			NoobEngine::Container::SList<int32_t> listInt1;

			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			int32_t int4 = 100;
			int32_t int5 = 200;

			listInt1.PushBack(int1);
			listInt1.PushBack(int2);
			listInt1.PushBack(int3);
			listInt1.PushBack(int4);

			listInt1.Remove(int1);

			Assert::AreEqual((uint32_t)3, listInt1.Size());
			Assert::AreEqual(int2, listInt1.Front());
			Assert::ExpectException<exception>([&]
			{
				*listInt1.Find(int1);
			});
			Assert::AreEqual(int4, listInt1.Back());

			listInt1.Remove(int3);
			Assert::AreEqual((uint32_t)2, listInt1.Size());
			Assert::ExpectException<exception>([&]
			{
				*listInt1.Find(int3);
			});
			Assert::AreEqual(int4, listInt1.Back());
			
			listInt1.Remove(int5);
			Assert::AreEqual((uint32_t)2, listInt1.Size());
			Assert::ExpectException<exception>([&]
			{
				*listInt1.Find(int3);
			});
			Assert::AreEqual(int4, listInt1.Back());

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			int32_t* intPtr4 = new int32_t(40);
			int32_t* intPtr5 = new int32_t(50);

			NoobEngine::Container::SList<int32_t*> listIntPtr1;

			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);
			listIntPtr1.PushBack(intPtr3);
			listIntPtr1.PushBack(intPtr4);

			listIntPtr1.Remove(intPtr1);

			Assert::AreEqual((uint32_t)3, listIntPtr1.Size());
			Assert::AreEqual(intPtr2, listIntPtr1.Front());
			Assert::ExpectException<exception>([&]
			{
				*listIntPtr1.Find(intPtr1);
			});
			Assert::AreEqual(intPtr4, listIntPtr1.Back());

			listIntPtr1.Remove(intPtr3);
			Assert::AreEqual((uint32_t)2, listIntPtr1.Size());
			Assert::ExpectException<exception>([&]
			{
				*listIntPtr1.Find(intPtr3);
			});
			Assert::AreEqual(intPtr4, listIntPtr1.Back());

			listIntPtr1.Remove(intPtr5);
			Assert::AreEqual((uint32_t)2, listIntPtr1.Size());
			Assert::ExpectException<exception>([&]
			{
				*listIntPtr1.Find(intPtr3);
			});
			Assert::AreEqual(intPtr4, listIntPtr1.Back());

			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);
			delete(intPtr4);
			delete(intPtr5);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1(10);
			Foo fooPtr2(20);
			Foo fooPtr3(30);
			Foo fooPtr4(40);
			Foo fooPtr5(50);

			NoobEngine::Container::SList<Foo> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);
			listFooPtr1.PushBack(fooPtr3);
			listFooPtr1.PushBack(fooPtr4);

			listFooPtr1.Remove(fooPtr1);

			Assert::AreEqual((uint32_t)3, listFooPtr1.Size());
			Assert::AreEqual(fooPtr2, listFooPtr1.Front());
			Assert::ExpectException<exception>([&]
			{
				*listFooPtr1.Find(fooPtr1);
			});
			Assert::AreEqual(fooPtr4, listFooPtr1.Back());

			listFooPtr1.Remove(fooPtr3);
			Assert::AreEqual((uint32_t)2, listFooPtr1.Size());
			Assert::ExpectException<exception>([&]
			{
				*listFooPtr1.Find(fooPtr3);
			});
			Assert::AreEqual(fooPtr4, listFooPtr1.Back());

			listFooPtr1.Remove(fooPtr5);
			Assert::AreEqual((uint32_t)2, listFooPtr1.Size());
			Assert::ExpectException<exception>([&]
			{
				*listFooPtr1.Find(fooPtr3);
			});
			Assert::AreEqual(fooPtr4, listFooPtr1.Back());
		}

		TEST_METHOD(Method_InsertAfter_Test)
		{
			//------------------------- int32_t----------------------------
			NoobEngine::Container::SList<int32_t> listInt1;

			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int4 = 40;
			int32_t int5 = 50;

			listInt1.PushBack(int1);
			listInt1.PushBack(int2);
			listInt1.PushBack(int4);
			listInt1.PushBack(int5);
			
			Assert::AreEqual((uint32_t)4, listInt1.Size());

			int32_t int3 = 30;
			Assert::AreEqual(int3, *listInt1.InsertAfter(int3, int2));

			Assert::AreEqual((uint32_t)5, listInt1.Size());
			
			int32_t int6 = 60;
			Assert::AreEqual(listInt1.end(), listInt1.InsertAfter(int6, int6));
			Assert::AreEqual((uint32_t)5, listInt1.Size());

			NoobEngine::Container::SList<int32_t>::Iterator list1IntItr = listInt1.Find(int3);
			NoobEngine::Container::SList<int32_t> listInt2;
			listInt2.PushBack(int1);
			listInt2.PushBack(int2);
			listInt2.PushBack(int3);
			listInt2.PushBack(int4);

			Assert::ExpectException<exception>([&]
			{
				listInt2.InsertAfter(int5, list1IntItr);
			});

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr4 = new int32_t(40);
			int32_t* intPtr5 = new int32_t(50);

			NoobEngine::Container::SList<int32_t*> listIntPtr1;
			listIntPtr1.PushBack(intPtr1);
			listIntPtr1.PushBack(intPtr2);
			listIntPtr1.PushBack(intPtr4);
			listIntPtr1.PushBack(intPtr5);

			int32_t* intPtr3 = new int32_t(30);
			int32_t* intPtr6 = new int32_t(60);
			Assert::AreEqual((uint32_t)4, listIntPtr1.Size());

			
			Assert::AreEqual(intPtr3, *listIntPtr1.InsertAfter(intPtr3, intPtr2));

			Assert::AreEqual((uint32_t)5, listIntPtr1.Size());
			
			
			Assert::AreEqual(listIntPtr1.end(), listIntPtr1.InsertAfter(intPtr6, intPtr6));
			Assert::AreEqual((uint32_t)5, listIntPtr1.Size());

			NoobEngine::Container::SList<int32_t*>::Iterator list1IntPtrItr = listIntPtr1.Find(intPtr3);
			NoobEngine::Container::SList<int32_t*> listIntPtr2;
			listIntPtr2.PushBack(intPtr1);
			listIntPtr2.PushBack(intPtr2);
			listIntPtr2.PushBack(intPtr3);
			listIntPtr2.PushBack(intPtr4);

			Assert::ExpectException<exception>([&]
			{
				listIntPtr2.InsertAfter(intPtr5, list1IntPtrItr);
			});

			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);
			delete(intPtr4);
			delete(intPtr5);
			delete(intPtr6);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1(10);
			Foo fooPtr2(20);
			Foo fooPtr4(40);
			Foo fooPtr5(50);
			NoobEngine::Container::SList<Foo> listFooPtr1;
			listFooPtr1.PushBack(fooPtr1);
			listFooPtr1.PushBack(fooPtr2);
			listFooPtr1.PushBack(fooPtr4);
			listFooPtr1.PushBack(fooPtr5);

			Assert::AreEqual((uint32_t)4, listFooPtr1.Size());

			Foo fooPtr3(30);
			Assert::AreEqual(fooPtr3, *listFooPtr1.InsertAfter(fooPtr3, fooPtr2));

			Assert::AreEqual((uint32_t)5, listFooPtr1.Size());
			
			Foo fooPtr6(60);
			Assert::AreEqual(listFooPtr1.end(), listFooPtr1.InsertAfter(fooPtr6, fooPtr6));
			Assert::AreEqual((uint32_t)5, listFooPtr1.Size());

			NoobEngine::Container::SList<Foo>::Iterator list1FooItr = listFooPtr1.Find(fooPtr3);
			NoobEngine::Container::SList<Foo> listFooPtr2;
			listFooPtr2.PushBack(fooPtr1);
			listFooPtr2.PushBack(fooPtr2);
			listFooPtr2.PushBack(fooPtr3);
			listFooPtr2.PushBack(fooPtr4);

			Assert::ExpectException<exception>([&]
			{
				listFooPtr2.InsertAfter(fooPtr5, list1FooItr);
			});
		}
		private:
			static _CrtMemState sStartMemState;
	   };

	   _CrtMemState SListTest::sStartMemState;
}