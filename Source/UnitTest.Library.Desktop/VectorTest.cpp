#include "pch.h"
#include "CppUnitTest.h"
#include "Container/Vector.h"
#include "SupportingClasses/Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NoobEngine::Container;
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

			template<> std::wstring ToString<NoobEngine::Container::Vector<int32_t>::Iterator>(typename const NoobEngine::Container::Vector<int32_t>::Iterator&)
			{
				std::wstringstream stringStream;
				stringStream << "Vector Int Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<NoobEngine::Container::Vector<int32_t*>::Iterator>(typename const NoobEngine::Container::Vector<int32_t*>::Iterator&)
			{
				std::wstringstream stringStream;
				stringStream << "Vector Int* Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<NoobEngine::Container::Vector<Foo>::Iterator>(typename const NoobEngine::Container::Vector<Foo>::Iterator&)
			{
				std::wstringstream stringStream;
				stringStream << "Vector Foo Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}
		}
	}
}

namespace UnitTestLibraryDesktop
{
	// template class that can be used to run tests on any type of data
	template<typename T>
	class VectorTestFunctions
	{
	public:
		static void TestDefaultConstructor()
		{
			Vector<T> sampleVector;
			uint32_t initialSize = 0;
			Assert::AreEqual(initialSize, sampleVector.Size());
			Assert::AreEqual((uint32_t)_DEFAULT_INIT_CAPACITY_, sampleVector.Capacity());
			Assert::AreEqual(sampleVector.begin(), sampleVector.end());
		}

		static void TestCopyConstructor(T& pValue1)
		{
			Vector<T> sampleVector;
			Assert::AreEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)0, sampleVector.Size());

			sampleVector.PushBack(pValue1);
			Assert::AreNotEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)1, sampleVector.Size());

			// calling copy
			Vector<T> sampleVector2(sampleVector);
			// testing for all private members
			Assert::AreEqual(sampleVector.Size(), sampleVector2.Size());
			Assert::AreEqual(sampleVector.Capacity(), sampleVector2.Capacity());
			Assert::AreEqual(sampleVector.GetCapacityIncrementStep(), sampleVector2.GetCapacityIncrementStep());

			// testing for data stored
			Assert::AreEqual(sampleVector.Front(), sampleVector2.Front());
			Assert::AreEqual(sampleVector.Back(), sampleVector2.Back());

			Assert::AreEqual(sampleVector.PopBack(), sampleVector2.PopBack());
		}

		static void TestAssignmentOpertor(T& pValue1, T& pValue2, T& pValue3)
		{
			Vector<T> sampleVector1;
			sampleVector1.PushBack(pValue1);
			sampleVector1.PushBack(pValue2);
			sampleVector1.PushBack(pValue3);

			Vector<T> sampleVector2;
			Assert::AreEqual((uint32_t)0, sampleVector2.Size());
			sampleVector2 = sampleVector1;
			
			Assert::AreEqual(sampleVector1.Size(), sampleVector2.Size());
			Assert::AreEqual(sampleVector1.Front(), sampleVector2.Front());
			Assert::AreEqual(sampleVector1.Back(), sampleVector2.Back());

			Assert::AreEqual(sampleVector1.PopBack(), sampleVector2.PopBack());
		}

		static void TestIsEmpty()
		{
			Vector<T> sampleVector;
			Assert::AreEqual(true, sampleVector.IsEmpty());
		}

		static void TestPushBack(T& pValue1, T& pValue2, T& pValue3)
		{
			Vector<T> sampleVector;
			Assert::AreEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)0, sampleVector.Size());

			sampleVector.PushBack(pValue1);
			sampleVector.PushBack(pValue2);
			sampleVector.PushBack(pValue3);

			Assert::AreNotEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)3, sampleVector.Size());
			Assert::AreEqual(pValue1, sampleVector.Front());
			Assert::AreEqual(pValue3, sampleVector.Back());
		}

		static void TestPopBack(T& pValue1, T& pValue2, T& pValue3)
		{
			Vector<T> sampleVector;
			Assert::AreEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)0, sampleVector.Size());

			sampleVector.PushBack(pValue1);
			sampleVector.PushBack(pValue2);
			sampleVector.PushBack(pValue3);

			Assert::AreNotEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)3, sampleVector.Size());
			Assert::AreEqual(pValue1, sampleVector.Front());
			Assert::AreEqual(pValue3, sampleVector.Back());

			Assert::AreEqual(pValue3, sampleVector.PopBack());
			Assert::AreEqual((uint32_t)2, sampleVector.Size());

			Assert::AreEqual(pValue2, sampleVector.PopBack());
			Assert::AreEqual((uint32_t)1, sampleVector.Size());

			Assert::AreEqual(pValue1, sampleVector.PopBack());
			Assert::AreEqual((uint32_t)0, sampleVector.Size());

			// calling pop back on empty array
			Assert::ExpectException<std::exception>([&] { sampleVector.PopBack(); });
		}

		static void TestBeginEnd(T& pValue1, T& pValue2, T& pValue3)
		{
			Vector<T> sampleVector;
			Assert::AreEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)0, sampleVector.Size());

			sampleVector.PushBack(pValue1);
			sampleVector.PushBack(pValue2);
			sampleVector.PushBack(pValue3);

			Assert::AreEqual(pValue1, *sampleVector.begin());
			Assert::ExpectException<std::exception>([&] { *sampleVector.end(); });
		}

		static void TestReserveCapacity(T& pValue1, T& pValue2, T& pValue3)
		{
			uint32_t initialCapacity = 2;
			// creating vector with capacity 2
			Vector<T> sampleVector(initialCapacity);
			Assert::AreEqual((uint32_t)0, sampleVector.Size());
			Assert::AreEqual(initialCapacity, sampleVector.Capacity());

			sampleVector.PushBack(pValue1);
			Assert::AreEqual((uint32_t)1, sampleVector.Size());
			Assert::AreEqual(initialCapacity, sampleVector.Capacity());

			sampleVector.PushBack(pValue2);
			Assert::AreEqual((uint32_t)2, sampleVector.Size());
			Assert::AreEqual(initialCapacity, sampleVector.Capacity());

			sampleVector.PushBack(pValue3);
			Assert::AreEqual((uint32_t)3, sampleVector.Size());
			Assert::AreNotEqual(initialCapacity, sampleVector.Capacity());
			Assert::AreEqual(initialCapacity + sampleVector.GetCapacityIncrementStep(), sampleVector.Capacity());
			// checking data
			Assert::AreEqual(pValue1, sampleVector.Front());
			Assert::AreEqual(pValue3, sampleVector.Back());

			// calling reserve to increase capacity
			// pCapacity < mSize
			// shrink to fit condition
			sampleVector.Reserve(initialCapacity);
			Assert::AreEqual((uint32_t)3, sampleVector.Size());
			Assert::AreEqual(sampleVector.Size(), sampleVector.Capacity());
			// checking data
			Assert::AreEqual(pValue1, sampleVector.Front());
			Assert::AreEqual(pValue3, sampleVector.Back());

			// calling reserve to increase capacity
			// pCapacity > mCapacity
			// increase the capacity
			uint32_t moreCaacity = 10;
			sampleVector.Reserve(moreCaacity);
			Assert::AreEqual((uint32_t)3, sampleVector.Size());
			Assert::AreEqual(moreCaacity, sampleVector.Capacity());
			// checking data
			Assert::AreEqual(pValue1, sampleVector.Front());
			Assert::AreEqual(pValue3, sampleVector.Back());


			// calling reserve to increase capacity
			// pCapacity == mCapacity
			// do nothing
			sampleVector.Reserve(moreCaacity);
			Assert::AreEqual((uint32_t)3, sampleVector.Size());
			Assert::AreEqual(moreCaacity, sampleVector.Capacity());
			// checking data
			Assert::AreEqual(pValue1, sampleVector.Front());
			Assert::AreEqual(pValue3, sampleVector.Back());
		}

		static void TestClear(T& pValue1, T& pValue2, T& pValue3)
		{
			Vector<T> sampleVector;
			Assert::AreEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)0, sampleVector.Size());

			sampleVector.PushBack(pValue1);
			sampleVector.PushBack(pValue2);
			sampleVector.PushBack(pValue3);

			Assert::AreEqual((uint32_t)3, sampleVector.Size());
			
			sampleVector.Clear();
			Assert::AreEqual((uint32_t)0, sampleVector.Size());
			Assert::AreEqual((uint32_t)0, sampleVector.Capacity());
		}

		static void TestIndexOfOperator(T& pValue1, T& pValue2, T& pValue3)
		{
			Vector<T> sampleVector;
			Assert::AreEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)0, sampleVector.Size());

			sampleVector.PushBack(pValue1);
			sampleVector.PushBack(pValue2);
			sampleVector.PushBack(pValue3);

			Assert::AreEqual((uint32_t)3, sampleVector.Size());
			Assert::AreEqual(pValue1, sampleVector[0]);
			Assert::AreEqual(pValue2, sampleVector[1]);
			Assert::AreEqual(pValue3, sampleVector[2]);

			Assert::AreEqual(pValue1, sampleVector.Front());
			Assert::AreEqual(pValue3, sampleVector.Back());

			// swapping first and second elements in the vector
			T temp = sampleVector[1];
			sampleVector[1] = sampleVector[0];
			sampleVector[0] = temp;

			Assert::AreEqual(pValue2, sampleVector[0]);
			Assert::AreEqual(pValue1, sampleVector[1]);
			Assert::AreEqual(pValue3, sampleVector[2]);

			Assert::AreEqual(pValue2, sampleVector.Front());
			Assert::AreEqual(pValue3, sampleVector.Back());

			// accessing out of index
			Assert::ExpectException<std::exception>([&] { sampleVector[10]; });

			const Vector<T>& constVector = sampleVector;
			Assert::AreEqual(pValue2, constVector[0]);
			Assert::AreEqual(pValue1, constVector[1]);
			Assert::AreEqual(pValue3, constVector[2]);

			Assert::AreEqual(pValue2, constVector.Front());
			Assert::AreEqual(pValue3, constVector.Back());
		}

		static void TestFind(T& pValue1, T& pValue2, T& pValue3)
		{
			Vector<T> sampleVector;
			Assert::AreEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)0, sampleVector.Size());

			sampleVector.PushBack(pValue1);
			sampleVector.PushBack(pValue2);
			sampleVector.PushBack(pValue3);

			Assert::AreEqual((uint32_t)3, sampleVector.Size());

			Assert::AreEqual(pValue2, *sampleVector.Find(pValue2));

			// popped last element (pValue3)
			sampleVector.PopBack();
			// trying to find pValue3
			Vector<T>::Iterator itr1 = sampleVector.end();
			Vector<T>::Iterator itr2 = sampleVector.Find(pValue3);
			Assert::AreEqual(sampleVector.end(), sampleVector.Find(pValue3));
		}

		static void TestRemove(T& pValue1, T& pValue2, T& pValue3, T& pValue4)
		{
			Vector<T> sampleVector;
			Assert::AreEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)0, sampleVector.Size());

			sampleVector.PushBack(pValue1);
			sampleVector.PushBack(pValue2);
			sampleVector.PushBack(pValue3);
			sampleVector.PushBack(pValue4);

			Assert::AreEqual((uint32_t)4, sampleVector.Size());

			// removing pValue3
			sampleVector.Remove(pValue3);

			Assert::AreEqual((uint32_t)3, sampleVector.Size());
			Assert::AreEqual(sampleVector.end(), sampleVector.Find(pValue3));

			sampleVector.Remove(sampleVector.Find(pValue1), sampleVector.Find(pValue4));
			Assert::AreEqual((uint32_t)1, sampleVector.Size());
		}

		class ReserveFunctorAwesome : public Vector<T>::ReserveFunction
		{
			virtual uint32_t operator() (uint32_t pSize, uint32_t pCapacity)
			{
				pSize;
				if (pCapacity > 0)
				{
					return pCapacity * 2;
				}
				else
				{
					return 10;
				}
			}
		};

		static void TestReserveFunctor(T& pValue1, T& pValue2, T& pValue3)
		{
			Vector<T> sampleVector;
			Assert::AreEqual(sampleVector.begin(), sampleVector.end());
			Assert::AreEqual((uint32_t)0, sampleVector.Size());

			sampleVector.PushBack(pValue1);
			sampleVector.PushBack(pValue2);
			sampleVector.PushBack(pValue3);

			uint32_t initialCapacity = sampleVector.Capacity();
			uint32_t capacityAfterDefaultStep = initialCapacity + sampleVector.GetCapacityIncrementStep();

			Vector<T>::ReserveFunction defaultFunctor;

			sampleVector.Reserve(defaultFunctor);
			// calling using default functor implementation
			Assert::AreEqual(capacityAfterDefaultStep, sampleVector.Capacity());

			// using awesome functor
			initialCapacity = sampleVector.Capacity();
			uint32_t capacityAfterAwesomeFunctor = initialCapacity * 2;
			ReserveFunctorAwesome awesomeFunctor;

			sampleVector.Reserve(awesomeFunctor);
			Assert::AreEqual(capacityAfterAwesomeFunctor, sampleVector.Capacity());
		}
	};

	TEST_CLASS(VectorTest)
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

		TEST_METHOD(Vector_Constructor_Default)
		{
			VectorTestFunctions<int32_t>::TestDefaultConstructor();
			VectorTestFunctions<int32_t*>::TestDefaultConstructor();
			VectorTestFunctions<Foo>::TestDefaultConstructor();
		}

		TEST_METHOD(Vector_Constructor_Copy)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			VectorTestFunctions<int32_t>::TestCopyConstructor(int1);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			VectorTestFunctions<int32_t*>::TestCopyConstructor(intPtr1);
			// freeing memory
			delete(intPtr1);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1;
			VectorTestFunctions<Foo>::TestCopyConstructor(fooPtr1);
		}

		TEST_METHOD(Vector_Assignment_Operator)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			VectorTestFunctions<int32_t>::TestAssignmentOpertor(int1, int2, int3);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			VectorTestFunctions<int32_t*>::TestAssignmentOpertor(intPtr1, intPtr2, intPtr3);
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1;
			Foo fooPtr2;
			Foo fooPtr3;
			VectorTestFunctions<Foo>::TestAssignmentOpertor(fooPtr1, fooPtr2, fooPtr3);
		}

		TEST_METHOD(Vector_IsEmpty)
		{
			VectorTestFunctions<int32_t>::TestIsEmpty();
			VectorTestFunctions<int32_t*>::TestIsEmpty();
			VectorTestFunctions<Foo>::TestIsEmpty();
		}

		TEST_METHOD(Vector_PushBack_Front_Back)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			VectorTestFunctions<int32_t>::TestPushBack(int1, int2, int3);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			VectorTestFunctions<int32_t*>::TestPushBack(intPtr1, intPtr2, intPtr3);
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1;
			Foo fooPtr2;
			Foo fooPtr3;
			VectorTestFunctions<Foo>::TestPushBack(fooPtr1, fooPtr2, fooPtr3);
		}

		TEST_METHOD(Vector_PopBack_Front_Back)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			VectorTestFunctions<int32_t>::TestPopBack(int1, int2, int3);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			VectorTestFunctions<int32_t*>::TestPopBack(intPtr1, intPtr2, intPtr3);
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1;
			Foo fooPtr2;
			Foo fooPtr3;
			VectorTestFunctions<Foo>::TestPopBack(fooPtr1, fooPtr2, fooPtr3);
		}

		TEST_METHOD(Vector_Begin_End)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			VectorTestFunctions<int32_t>::TestBeginEnd(int1, int2, int3);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			VectorTestFunctions<int32_t*>::TestBeginEnd(intPtr1, intPtr2, intPtr3);
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1;
			Foo fooPtr2;
			Foo fooPtr3;
			VectorTestFunctions<Foo>::TestBeginEnd(fooPtr1, fooPtr2, fooPtr3);
		}

		TEST_METHOD(Vector_Reserver_Capacity)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			VectorTestFunctions<int32_t>::TestReserveCapacity(int1, int2, int3);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			VectorTestFunctions<int32_t*>::TestReserveCapacity(intPtr1, intPtr2, intPtr3);
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1;
			Foo fooPtr2;
			Foo fooPtr3;
			VectorTestFunctions<Foo>::TestReserveCapacity(fooPtr1, fooPtr2, fooPtr3);
		}

		TEST_METHOD(Vector_Clear)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			VectorTestFunctions<int32_t>::TestClear(int1, int2, int3);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			VectorTestFunctions<int32_t*>::TestClear(intPtr1, intPtr2, intPtr3);
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1;
			Foo fooPtr2;
			Foo fooPtr3;
			VectorTestFunctions<Foo>::TestClear(fooPtr1, fooPtr2, fooPtr3);
		}

		TEST_METHOD(Vector_IndexOf_Operator)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			VectorTestFunctions<int32_t>::TestIndexOfOperator(int1, int2, int3);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			VectorTestFunctions<int32_t*>::TestIndexOfOperator(intPtr1, intPtr2, intPtr3);
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1(10);
			Foo fooPtr2;
			Foo fooPtr3;
			VectorTestFunctions<Foo>::TestIndexOfOperator(fooPtr1, fooPtr2, fooPtr3);
		}

		TEST_METHOD(Vector_Find)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			VectorTestFunctions<int32_t>::TestFind(int1, int2, int3);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			VectorTestFunctions<int32_t*>::TestFind(intPtr1, intPtr2, intPtr3);
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1(10);
			Foo fooPtr2(20);
			Foo fooPtr3(30);
			VectorTestFunctions<Foo>::TestFind(fooPtr1, fooPtr2, fooPtr3);
		}

		TEST_METHOD(Vector_Remove)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			int32_t int4 = 40;
			VectorTestFunctions<int32_t>::TestRemove(int1, int2, int3, int4);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			int32_t* intPtr4 = new int32_t(40);
			VectorTestFunctions<int32_t*>::TestRemove(intPtr1, intPtr2, intPtr3, intPtr4);
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);
			delete(intPtr4);

			//------------------------Foo pointer-------------------------
			Foo fooPtr1(10);
			Foo fooPtr2(20);
			Foo fooPtr3(30);
			Foo fooPtr4(40);
			VectorTestFunctions<Foo>::TestRemove(fooPtr1, fooPtr2, fooPtr3, fooPtr4);
		}

		TEST_METHOD(Vector_Reserve_Functor)
		{
			//------------------------- int32_t----------------------------
			int32_t int1 = 10;
			int32_t int2 = 20;
			int32_t int3 = 30;
			VectorTestFunctions<int32_t>::TestReserveFunctor(int1, int2, int3);

			//-----------------------int32_t pointer----------------------
			int32_t* intPtr1 = new int32_t(10);
			int32_t* intPtr2 = new int32_t(20);
			int32_t* intPtr3 = new int32_t(30);
			VectorTestFunctions<int32_t*>::TestReserveFunctor(intPtr1, intPtr2, intPtr3);
			// freeing memory
			delete(intPtr1);
			delete(intPtr2);
			delete(intPtr3);
			
			//------------------------Foo pointer-------------------------
			Foo fooPtr1(10);
			Foo fooPtr2(20);
			Foo fooPtr3(30);
			VectorTestFunctions<Foo>::TestReserveFunctor(fooPtr1, fooPtr2, fooPtr3);
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;

	
}