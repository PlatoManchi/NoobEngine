#include "pch.h"
#include "CppUnitTest.h"
#include "Container/Hashmap.h"
#include "SupportingClasses/Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NoobEngine::Container;
using namespace SupportingClasses;


namespace UnitTestLibraryDesktop
{
	class FooHashFunction
	{
	public:
		FooHashFunction() {}
		inline uint32_t operator()(Foo pParam) const
		{
			return 0U;
		}
	};
}

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			// adding helper function to namespace for assert to compare two foo objects and pointers


			/*template<> std::wstring ToString<Foo>(const Foo& t)
			{
				std::wstringstream stringStream;
				stringStream << "Foo_" << (t.mID);
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}*/
			
#pragma region FooHashFunctor
			/*template<> std::wstring ToString<UnitTestLibraryDesktop::FooHashFunction>(const UnitTestLibraryDesktop::FooHashFunction&)
			{
				std::wstringstream stringStream;
				stringStream << "FooHashFunction";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}*/
#pragma endregion
#pragma region IteratorToString
			template<> std::wstring ToString<Hashmap<int32_t, int32_t>::Iterator>(typename const Hashmap<int32_t, int32_t>::Iterator&)
			{
				std::wstringstream stringStream;
				stringStream << "Hashmap int, int Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<Hashmap<int32_t*, int32_t>::Iterator>(typename const Hashmap<int32_t*, int32_t>::Iterator&)
			{
				std::wstringstream stringStream;
				stringStream << "Hashmap int*, int Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<Hashmap<char*, int32_t>::Iterator>(typename const Hashmap<char*, int32_t>::Iterator&)
			{
				std::wstringstream stringStream;
				stringStream << "Hashmap int*, int Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<Hashmap<std::string, int32_t>::Iterator>(typename const Hashmap<std::string, int32_t>::Iterator&)
			{
				std::wstringstream stringStream;
				stringStream << "Hashmap std::string, int Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<Hashmap<Foo, int32_t>::Iterator>(typename const Hashmap<Foo, int32_t>::Iterator&)
			{
				std::wstringstream stringStream;
				stringStream << "Hashmap Foo, int Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<Hashmap<Foo*, int32_t>::Iterator>(typename const Hashmap<Foo*, int32_t>::Iterator&)
			{
				std::wstringstream stringStream;
				stringStream << "Hashmap Foo*, int Iterator_";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}
#pragma endregion
#pragma region PairToString
			template<> std::wstring ToString<std::pair<int32_t, int32_t>>(const std::pair<int32_t, int32_t>&)
			{
				std::wstringstream stringStream;
				stringStream << "std::pair int, int";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<std::pair<int32_t*, int32_t>>(const std::pair<int32_t*, int32_t>&)
			{
				std::wstringstream stringStream;
				stringStream << "std::pair int*, int";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<std::pair<char*, int32_t>>(const std::pair<char*, int32_t>&)
			{
				std::wstringstream stringStream;
				stringStream << "std::pair char*, int";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<std::pair<std::string, int32_t>>(const std::pair<std::string, int32_t>&)
			{
				std::wstringstream stringStream;
				stringStream << "std::pair std::string, int";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<std::pair<Foo, int32_t>>(const std::pair<Foo, int32_t>&)
			{
				std::wstringstream stringStream;
				stringStream << "std::pair Foo, int";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}

			template<> std::wstring ToString<std::pair<Foo*, int32_t>>(const std::pair<Foo*, int32_t>&)
			{
				std::wstringstream stringStream;
				stringStream << "std::pair Foo*, int";
				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}
#pragma endregion
		}
	}
}


namespace UnitTestLibraryDesktop
{
	template <typename TKey, typename TValue, typename HashFunctor = DefaultHashFunction<TKey>>
	class HashmapTestFunctions
	{
	public:
		static void TestHashmapConstructor()
		{
			Hashmap<TKey, TValue> sampleMap;
			uint32_t initialSize = 0;
			Assert::AreEqual(initialSize, sampleMap.Size());
			Assert::AreEqual(sampleMap.begin(), sampleMap.end());
		}

		static void TestHashmapCopyConstructor(std::pair<TKey, TValue> pValue1)
		{
			// setting stage for testing
			Hashmap<TKey, TValue, HashFunctor> sampleMap;
			uint32_t initialSize = 0;
			Assert::AreEqual(initialSize, sampleMap.Size());
			Assert::IsTrue(sampleMap.begin() == sampleMap.end());
			//Assert::AreEqual(sampleMap.begin(), sampleMap.end());

			sampleMap.Insert(pValue1);
			//Assert::AreNotEqual(sampleMap.begin(), sampleMap.end());
			Assert::IsFalse(sampleMap.begin() == sampleMap.end());
			Assert::AreEqual(1U, sampleMap.Size());

			// calling copy
			Hashmap<TKey, TValue, HashFunctor> sampleMap2(sampleMap);
			//testing for all members
			Assert::AreEqual(sampleMap.Size(), sampleMap2.Size());

			// testing for data 
			Assert::AreEqual(true, sampleMap.ContainsKey(pValue1.first));
			Assert::AreEqual(true, sampleMap2.ContainsKey(pValue1.first));

		}

		static void TestHashmapAssignemntOperator(std::pair<TKey, TValue>& pValue1, std::pair<TKey, TValue>& pValue2, std::pair<TKey, TValue>& pValue3)
		{
			Hashmap<TKey, TValue, HashFunctor> sampleMap1;
			sampleMap1.Insert(pValue1);
			sampleMap1.Insert(pValue2);
			sampleMap1.Insert(pValue3);

			Hashmap<TKey, TValue, HashFunctor> sampleMap2;
			Assert::AreEqual(0U, sampleMap2.Size());
			sampleMap2 = sampleMap1;

			Assert::AreEqual(sampleMap1.Size(), sampleMap2.Size());
			Assert::AreEqual(sampleMap1[pValue1.first], sampleMap2[pValue1.first]);
			Assert::AreEqual(sampleMap1[pValue2.first], sampleMap2[pValue2.first]);
			Assert::AreEqual(sampleMap1[pValue3.first], sampleMap2[pValue3.first]);
		}

		static void TestHashmapInsert(std::pair<TKey, TValue>& pValue1, std::pair<TKey, TValue>& pValue2, std::pair<TKey, TValue>& pValue3)
		{
			Hashmap<TKey, TValue, HashFunctor> sampleMap;
			Assert::AreEqual(0U, sampleMap.Size());

			sampleMap.Insert(pValue1);
			Assert::AreEqual(1U, sampleMap.Size());

			// inserting same element again shouldn't result in increasing size
			sampleMap.Insert(pValue1);
			Assert::AreEqual(1U, sampleMap.Size());

			sampleMap.Insert(pValue2);
			Assert::AreEqual(2U, sampleMap.Size());

			sampleMap.Insert(pValue3);
			Assert::AreEqual(3U, sampleMap.Size());
		}

		static void TestHashmapFind(std::pair<TKey, TValue>& pValue1, std::pair<TKey, TValue>& pValue2, std::pair<TKey, TValue>& pValue3)
		{
			Hashmap<TKey, TValue, HashFunctor> sampleMap;
			Assert::AreEqual(0U, sampleMap.Size());

			sampleMap.Insert(pValue1);
			Assert::AreEqual(1U, sampleMap.Size());

			sampleMap.Insert(pValue2);
			Assert::AreEqual(2U, sampleMap.Size());
			Assert::IsTrue(sampleMap.end() == sampleMap.Find(pValue3.first));
			
			typename Hashmap<TKey, TValue, HashFunctor>::Iterator itr = sampleMap.Insert(pValue3);
			Assert::IsTrue(itr == sampleMap.Find(pValue3.first));
			
			Assert::AreEqual(pValue1, *sampleMap.Find(pValue1.first));
			Assert::AreEqual(pValue2, *sampleMap.Find(pValue2.first));
			Assert::AreEqual(pValue3, *sampleMap.Find(pValue3.first));
		}

		static void TestHashmapConstainsKey(std::pair<TKey, TValue>& pValue1, std::pair<TKey, TValue>& pValue2, std::pair<TKey, TValue>& pValue3)
		{
			Hashmap<TKey, TValue, HashFunctor> sampleMap;
			Assert::AreEqual(0U, sampleMap.Size());

			sampleMap.Insert(pValue1);
			Assert::AreEqual(1U, sampleMap.Size());

			sampleMap.Insert(pValue2);
			Assert::AreEqual(2U, sampleMap.Size());
			Assert::AreEqual(false, sampleMap.ContainsKey(pValue3.first));

			typename Hashmap<TKey, TValue, HashFunctor>::Iterator itr = sampleMap.Insert(pValue3);
			Assert::AreEqual(true, sampleMap.ContainsKey(pValue3.first));
		}

		static void TestHashmapRemove(std::pair<TKey, TValue>& pValue1, std::pair<TKey, TValue>& pValue2, std::pair<TKey, TValue>& pValue3)
		{
			Hashmap<TKey, TValue, HashFunctor> sampleMap;
			Assert::AreEqual(0U, sampleMap.Size());

			sampleMap.Insert(pValue1);
			Assert::AreEqual(1U, sampleMap.Size());

			sampleMap.Insert(pValue2);
			Assert::AreEqual(2U, sampleMap.Size());
			Assert::AreEqual(false, sampleMap.ContainsKey(pValue3.first));
			sampleMap.Remove(pValue3.first);
			Assert::AreEqual(2U, sampleMap.Size());

			typename Hashmap<TKey, TValue, HashFunctor>::Iterator itr = sampleMap.Insert(pValue3);
			Assert::AreEqual(true, sampleMap.ContainsKey(pValue3.first));
			Assert::AreEqual(3U, sampleMap.Size());
			sampleMap.Remove(pValue3.first);
			Assert::AreEqual(2U, sampleMap.Size());
		}

		static void TestHashmapClear(std::pair<TKey, TValue>& pValue1, std::pair<TKey, TValue>& pValue2, std::pair<TKey, TValue>& pValue3)
		{
			Hashmap<TKey, TValue, HashFunctor> sampleMap;
			Assert::AreEqual(0U, sampleMap.Size());
			Assert::IsTrue(sampleMap.begin() == sampleMap.end());
			//Assert::AreEqual(sampleMap.begin(), sampleMap.end());


			sampleMap[pValue1.first] = pValue1.second;
			sampleMap[pValue2.first] = pValue2.second;
			sampleMap[pValue3.first] = pValue3.second;

			Assert::AreEqual(3U, sampleMap.Size());
			Assert::IsFalse(sampleMap.begin() == sampleMap.end());
			//Assert::AreNotEqual(sampleMap.begin(), sampleMap.end());

			sampleMap.Clear();

			Assert::AreEqual(0U, sampleMap.Size());
			Hashmap<TKey, TValue, HashFunctor>::Iterator beginItr = sampleMap.begin();
			Hashmap<TKey, TValue, HashFunctor>::Iterator endItr = sampleMap.end();
			Assert::IsTrue(sampleMap.begin() == sampleMap.end());
			//Assert::AreEqual(sampleMap.begin(), sampleMap.end());
		}

		static void TestHashmapBracketOperator(std::pair<TKey, TValue>& pValue1, std::pair<TKey, TValue>& pValue2, std::pair<TKey, TValue>& pValue3)
		{
			Hashmap<TKey, TValue, HashFunctor> sampleMap;
			Assert::AreEqual(0U, sampleMap.Size());
			Assert::IsTrue(sampleMap.begin() == sampleMap.end());
			//Assert::AreEqual(sampleMap.begin(), sampleMap.end());

			sampleMap.Insert(pValue1);
			sampleMap.Insert(pValue2);
			sampleMap[pValue3.first] = pValue3.second;
			
			Assert::AreEqual(3U, sampleMap.Size());
			sampleMap[pValue3.first] = pValue3.second;

			Assert::AreEqual(3U, sampleMap.Size());

			Assert::AreEqual(pValue1.second, sampleMap[pValue1.first]);
			Assert::AreEqual(pValue2.second, sampleMap[pValue2.first]);
			Assert::AreEqual(pValue3.second, sampleMap[pValue3.first]);

			const Hashmap<TKey, TValue, HashFunctor> sampleMap2 = sampleMap;
			Assert::AreEqual(pValue1.second, sampleMap2[pValue1.first]);
			Assert::AreEqual(pValue2.second, sampleMap2[pValue2.first]);
			Assert::AreEqual(pValue3.second, sampleMap2[pValue3.first]);
		}
	};



	TEST_CLASS(HashmapTest)
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

		TEST_METHOD(Hashmap_Constructor)
		{
			HashmapTestFunctions<int32_t, int32_t>::TestHashmapConstructor();
			HashmapTestFunctions<int32_t*, int32_t>::TestHashmapConstructor();
			HashmapTestFunctions<char*, int32_t>::TestHashmapConstructor();
			HashmapTestFunctions<std::string, int32_t>::TestHashmapConstructor();
			HashmapTestFunctions<Foo, int32_t, FooHashFunction>::TestHashmapConstructor();
			HashmapTestFunctions<Foo*, int32_t>::TestHashmapConstructor();
		}

		TEST_METHOD(Hashmap_Copy_Constructor)
		{
			// ---------------------- int32_t, int32_t ---------------------------
			int32_t key = 10;
			int32_t value = 100;
			std::pair<int32_t, int32_t> keyvaluePair(key, value);
			HashmapTestFunctions<int32_t, int32_t>::TestHashmapCopyConstructor(keyvaluePair);

			// ---------------------- int32_t*, int32_t ---------------------------
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr(&key, value);
			HashmapTestFunctions<int32_t*, int32_t>::TestHashmapCopyConstructor(keyvaluePairIntPtr);

			// ---------------------- char*, int32_t ---------------------------
			char* str = "Plato";
			std::pair<char*, int32_t> keyvaluePairCharPtr(str, value);
			HashmapTestFunctions<char*, int32_t>::TestHashmapCopyConstructor(keyvaluePairCharPtr);

			// ---------------------- std::String, int32_t ---------------------------
			std::pair<std::string, int32_t> keyvaluePairString(std::string(str), value);
			HashmapTestFunctions<std::string, int32_t>::TestHashmapCopyConstructor(keyvaluePairString);

			// ---------------------- Foo, int32_t ---------------------------
			Foo fooObj(10);
			std::pair<Foo, int32_t> keyvaluePairFoo(fooObj, value);
			HashmapTestFunctions<Foo, int32_t, FooHashFunction>::TestHashmapCopyConstructor(keyvaluePairFoo);

			// ---------------------- Foo*, int32_t ---------------------------
			std::pair<Foo*, int32_t> keyvaluePairFooPtr(&fooObj, value);
			HashmapTestFunctions<Foo*, int32_t>::TestHashmapCopyConstructor(keyvaluePairFooPtr);
		}

		TEST_METHOD(Hashmap_Assignment_Operator)
		{
			// ---------------------- int32_t, int32_t ---------------------------
			int32_t key1 = 10;
			int32_t key2 = 20;
			int32_t key3 = 30;
			int32_t value1 = 100;
			int32_t value2 = 200;
			int32_t value3 = 1300;
			std::pair<int32_t, int32_t> keyvaluePair1(key1, value1);
			std::pair<int32_t, int32_t> keyvaluePair2(key2, value2);
			std::pair<int32_t, int32_t> keyvaluePair3(key3, value3);
			HashmapTestFunctions<int32_t, int32_t>::TestHashmapAssignemntOperator(keyvaluePair1, keyvaluePair2, keyvaluePair3);

			// ---------------------- int32_t*, int32_t ---------------------------
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr1(&key1, value1);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr2(&key2, value2);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr3(&key3, value3);
			HashmapTestFunctions<int32_t*, int32_t>::TestHashmapAssignemntOperator(keyvaluePairIntPtr1, keyvaluePairIntPtr2, keyvaluePairIntPtr3);

			// ---------------------- char*, int32_t ---------------------------
			char* str1 = "Alpha";
			char* str2 = "Charlie";
			char* str3 = "Delta";
			std::pair<char*, int32_t> keyvaluePairCharPtr1(str1, value1);
			std::pair<char*, int32_t> keyvaluePairCharPtr2(str2, value2);
			std::pair<char*, int32_t> keyvaluePairCharPtr3(str3, value3);
			HashmapTestFunctions<char*, int32_t>::TestHashmapAssignemntOperator(keyvaluePairCharPtr1, keyvaluePairCharPtr2, keyvaluePairCharPtr3);

			// ---------------------- std::String, int32_t ---------------------------
			std::pair<std::string, int32_t> keyvaluePairString1(std::string(str1), value1);
			std::pair<std::string, int32_t> keyvaluePairString2(std::string(str2), value2);
			std::pair<std::string, int32_t> keyvaluePairString3(std::string(str3), value3);
			HashmapTestFunctions<std::string, int32_t>::TestHashmapAssignemntOperator(keyvaluePairString1, keyvaluePairString2, keyvaluePairString3);

			// ---------------------- Foo, int32_t ---------------------------
			Foo fooObj1(key1);
			Foo fooObj2(key2);
			Foo fooObj3(key3);
			std::pair<Foo, int32_t> keyvaluePairFoo1(fooObj1, value1);
			std::pair<Foo, int32_t> keyvaluePairFoo2(fooObj2, value2);
			std::pair<Foo, int32_t> keyvaluePairFoo3(fooObj3, value3);
			HashmapTestFunctions<Foo, int32_t, FooHashFunction>::TestHashmapAssignemntOperator(keyvaluePairFoo1, keyvaluePairFoo2, keyvaluePairFoo3);

			// ---------------------- Foo*, int32_t ---------------------------
			std::pair<Foo*, int32_t> keyvaluePairFooPtr1(&fooObj1, value1);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr2(&fooObj2, value2);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr3(&fooObj3, value3);
			HashmapTestFunctions<Foo*, int32_t>::TestHashmapAssignemntOperator(keyvaluePairFooPtr1, keyvaluePairFooPtr2, keyvaluePairFooPtr3);
		}

		TEST_METHOD(Hashmap_Insert)
		{
			// ---------------------- int32_t, int32_t ---------------------------
			int32_t key1 = 10;
			int32_t key2 = 20;
			int32_t key3 = 30;
			int32_t value1 = 100;
			int32_t value2 = 200;
			int32_t value3 = 1300;
			std::pair<int32_t, int32_t> keyvaluePair1(key1, value1);
			std::pair<int32_t, int32_t> keyvaluePair2(key2, value2);
			std::pair<int32_t, int32_t> keyvaluePair3(key3, value3);
			HashmapTestFunctions<int32_t, int32_t>::TestHashmapInsert(keyvaluePair1, keyvaluePair2, keyvaluePair3);

			// ---------------------- int32_t*, int32_t ---------------------------
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr1(&key1, value1);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr2(&key2, value2);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr3(&key3, value3);
			HashmapTestFunctions<int32_t*, int32_t>::TestHashmapInsert(keyvaluePairIntPtr1, keyvaluePairIntPtr2, keyvaluePairIntPtr3);

			// ---------------------- char*, int32_t ---------------------------
			char* str1 = "Alpha";
			char* str2 = "Charlie";
			char* str3 = "Delta";
			std::pair<char*, int32_t> keyvaluePairCharPtr1(str1, value1);
			std::pair<char*, int32_t> keyvaluePairCharPtr2(str2, value2);
			std::pair<char*, int32_t> keyvaluePairCharPtr3(str3, value3);
			HashmapTestFunctions<char*, int32_t>::TestHashmapInsert(keyvaluePairCharPtr1, keyvaluePairCharPtr2, keyvaluePairCharPtr3);

			// ---------------------- std::String, int32_t ---------------------------
			std::pair<std::string, int32_t> keyvaluePairString1(std::string(str1), value1);
			std::pair<std::string, int32_t> keyvaluePairString2(std::string(str2), value2);
			std::pair<std::string, int32_t> keyvaluePairString3(std::string(str3), value3);
			HashmapTestFunctions<std::string, int32_t>::TestHashmapInsert(keyvaluePairString1, keyvaluePairString2, keyvaluePairString3);

			// ---------------------- Foo, int32_t ---------------------------
			Foo fooObj1(key1);
			Foo fooObj2(key2);
			Foo fooObj3(key3);
			std::pair<Foo, int32_t> keyvaluePairFoo1(fooObj1, value1);
			std::pair<Foo, int32_t> keyvaluePairFoo2(fooObj2, value2);
			std::pair<Foo, int32_t> keyvaluePairFoo3(fooObj3, value3);
			HashmapTestFunctions<Foo, int32_t, FooHashFunction>::TestHashmapInsert(keyvaluePairFoo1, keyvaluePairFoo2, keyvaluePairFoo3);

			// ---------------------- Foo*, int32_t ---------------------------
			std::pair<Foo*, int32_t> keyvaluePairFooPtr1(&fooObj1, value1);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr2(&fooObj2, value2);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr3(&fooObj3, value3);
			HashmapTestFunctions<Foo*, int32_t>::TestHashmapInsert(keyvaluePairFooPtr1, keyvaluePairFooPtr2, keyvaluePairFooPtr3);
		}

		TEST_METHOD(Hashmap_Find)
		{
			// ---------------------- int32_t, int32_t ---------------------------
			int32_t key1 = 10;
			int32_t key2 = 20;
			int32_t key3 = 30;
			int32_t value1 = 100;
			int32_t value2 = 200;
			int32_t value3 = 1300;
			std::pair<int32_t, int32_t> keyvaluePair1(key1, value1);
			std::pair<int32_t, int32_t> keyvaluePair2(key2, value2);
			std::pair<int32_t, int32_t> keyvaluePair3(key3, value3);
			HashmapTestFunctions<int32_t, int32_t>::TestHashmapFind(keyvaluePair1, keyvaluePair2, keyvaluePair3);

			// ---------------------- int32_t*, int32_t ---------------------------
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr1(&key1, value1);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr2(&key2, value2);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr3(&key3, value3);
			HashmapTestFunctions<int32_t*, int32_t>::TestHashmapFind(keyvaluePairIntPtr1, keyvaluePairIntPtr2, keyvaluePairIntPtr3);

			// ---------------------- char*, int32_t ---------------------------
			char* str1 = "Alpha";
			char* str2 = "Charlie";
			char* str3 = "Delta";
			std::pair<char*, int32_t> keyvaluePairCharPtr1(str1, value1);
			std::pair<char*, int32_t> keyvaluePairCharPtr2(str2, value2);
			std::pair<char*, int32_t> keyvaluePairCharPtr3(str3, value3);
			HashmapTestFunctions<char*, int32_t>::TestHashmapFind(keyvaluePairCharPtr1, keyvaluePairCharPtr2, keyvaluePairCharPtr3);

			// ---------------------- std::String, int32_t ---------------------------
			std::pair<std::string, int32_t> keyvaluePairString1(std::string(str1), value1);
			std::pair<std::string, int32_t> keyvaluePairString2(std::string(str2), value2);
			std::pair<std::string, int32_t> keyvaluePairString3(std::string(str3), value3);
			HashmapTestFunctions<std::string, int32_t>::TestHashmapFind(keyvaluePairString1, keyvaluePairString2, keyvaluePairString3);

			// ---------------------- Foo, int32_t ---------------------------
			Foo fooObj1(key1);
			Foo fooObj2(key2);
			Foo fooObj3(key3);
			std::pair<Foo, int32_t> keyvaluePairFoo1(fooObj1, value1);
			std::pair<Foo, int32_t> keyvaluePairFoo2(fooObj2, value2);
			std::pair<Foo, int32_t> keyvaluePairFoo3(fooObj3, value3);
			HashmapTestFunctions<Foo, int32_t, FooHashFunction>::TestHashmapFind(keyvaluePairFoo1, keyvaluePairFoo2, keyvaluePairFoo3);

			// ---------------------- Foo*, int32_t ---------------------------
			std::pair<Foo*, int32_t> keyvaluePairFooPtr1(&fooObj1, value1);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr2(&fooObj2, value2);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr3(&fooObj3, value3);
			HashmapTestFunctions<Foo*, int32_t>::TestHashmapFind(keyvaluePairFooPtr1, keyvaluePairFooPtr2, keyvaluePairFooPtr3);
		}

		TEST_METHOD(Hashmap_ContainsKey)
		{
			// ---------------------- int32_t, int32_t ---------------------------
			int32_t key1 = 10;
			int32_t key2 = 20;
			int32_t key3 = 30;
			int32_t value1 = 100;
			int32_t value2 = 200;
			int32_t value3 = 1300;
			std::pair<int32_t, int32_t> keyvaluePair1(key1, value1);
			std::pair<int32_t, int32_t> keyvaluePair2(key2, value2);
			std::pair<int32_t, int32_t> keyvaluePair3(key3, value3);
			HashmapTestFunctions<int32_t, int32_t>::TestHashmapConstainsKey(keyvaluePair1, keyvaluePair2, keyvaluePair3);

			// ---------------------- int32_t*, int32_t ---------------------------
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr1(&key1, value1);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr2(&key2, value2);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr3(&key3, value3);
			HashmapTestFunctions<int32_t*, int32_t>::TestHashmapConstainsKey(keyvaluePairIntPtr1, keyvaluePairIntPtr2, keyvaluePairIntPtr3);

			// ---------------------- char*, int32_t ---------------------------
			char* str1 = "Alpha";
			char* str2 = "Charlie";
			char* str3 = "Delta";
			std::pair<char*, int32_t> keyvaluePairCharPtr1(str1, value1);
			std::pair<char*, int32_t> keyvaluePairCharPtr2(str2, value2);
			std::pair<char*, int32_t> keyvaluePairCharPtr3(str3, value3);
			HashmapTestFunctions<char*, int32_t>::TestHashmapConstainsKey(keyvaluePairCharPtr1, keyvaluePairCharPtr2, keyvaluePairCharPtr3);

			// ---------------------- std::String, int32_t ---------------------------
			std::pair<std::string, int32_t> keyvaluePairString1(std::string(str1), value1);
			std::pair<std::string, int32_t> keyvaluePairString2(std::string(str2), value2);
			std::pair<std::string, int32_t> keyvaluePairString3(std::string(str3), value3);
			HashmapTestFunctions<std::string, int32_t>::TestHashmapConstainsKey(keyvaluePairString1, keyvaluePairString2, keyvaluePairString3);

			// ---------------------- Foo, int32_t ---------------------------
			Foo fooObj1(key1);
			Foo fooObj2(key2);
			Foo fooObj3(key3);
			std::pair<Foo, int32_t> keyvaluePairFoo1(fooObj1, value1);
			std::pair<Foo, int32_t> keyvaluePairFoo2(fooObj2, value2);
			std::pair<Foo, int32_t> keyvaluePairFoo3(fooObj3, value3);
			HashmapTestFunctions<Foo, int32_t, FooHashFunction>::TestHashmapConstainsKey(keyvaluePairFoo1, keyvaluePairFoo2, keyvaluePairFoo3);

			// ---------------------- Foo*, int32_t ---------------------------
			std::pair<Foo*, int32_t> keyvaluePairFooPtr1(&fooObj1, value1);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr2(&fooObj2, value2);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr3(&fooObj3, value3);
			HashmapTestFunctions<Foo*, int32_t>::TestHashmapConstainsKey(keyvaluePairFooPtr1, keyvaluePairFooPtr2, keyvaluePairFooPtr3);
		}

		TEST_METHOD(Hashmap_Remove)
		{
			// ---------------------- int32_t, int32_t ---------------------------
			int32_t key1 = 10;
			int32_t key2 = 20;
			int32_t key3 = 30;
			int32_t value1 = 100;
			int32_t value2 = 200;
			int32_t value3 = 1300;
			std::pair<int32_t, int32_t> keyvaluePair1(key1, value1);
			std::pair<int32_t, int32_t> keyvaluePair2(key2, value2);
			std::pair<int32_t, int32_t> keyvaluePair3(key3, value3);
			HashmapTestFunctions<int32_t, int32_t>::TestHashmapRemove(keyvaluePair1, keyvaluePair2, keyvaluePair3);

			// ---------------------- int32_t*, int32_t ---------------------------
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr1(&key1, value1);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr2(&key2, value2);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr3(&key3, value3);
			HashmapTestFunctions<int32_t*, int32_t>::TestHashmapRemove(keyvaluePairIntPtr1, keyvaluePairIntPtr2, keyvaluePairIntPtr3);

			// ---------------------- char*, int32_t ---------------------------
			char* str1 = "Alpha";
			char* str2 = "Charlie";
			char* str3 = "Delta";
			std::pair<char*, int32_t> keyvaluePairCharPtr1(str1, value1);
			std::pair<char*, int32_t> keyvaluePairCharPtr2(str2, value2);
			std::pair<char*, int32_t> keyvaluePairCharPtr3(str3, value3);
			HashmapTestFunctions<char*, int32_t>::TestHashmapRemove(keyvaluePairCharPtr1, keyvaluePairCharPtr2, keyvaluePairCharPtr3);

			// ---------------------- std::String, int32_t ---------------------------
			std::pair<std::string, int32_t> keyvaluePairString1(std::string(str1), value1);
			std::pair<std::string, int32_t> keyvaluePairString2(std::string(str2), value2);
			std::pair<std::string, int32_t> keyvaluePairString3(std::string(str3), value3);
			HashmapTestFunctions<std::string, int32_t>::TestHashmapRemove(keyvaluePairString1, keyvaluePairString2, keyvaluePairString3);

			// ---------------------- Foo, int32_t ---------------------------
			Foo fooObj1(key1);
			Foo fooObj2(key2);
			Foo fooObj3(key3);
			std::pair<Foo, int32_t> keyvaluePairFoo1(fooObj1, value1);
			std::pair<Foo, int32_t> keyvaluePairFoo2(fooObj2, value2);
			std::pair<Foo, int32_t> keyvaluePairFoo3(fooObj3, value3);
			HashmapTestFunctions<Foo, int32_t, FooHashFunction>::TestHashmapRemove(keyvaluePairFoo1, keyvaluePairFoo2, keyvaluePairFoo3);

			// ---------------------- Foo*, int32_t ---------------------------
			std::pair<Foo*, int32_t> keyvaluePairFooPtr1(&fooObj1, value1);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr2(&fooObj2, value2);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr3(&fooObj3, value3);
			HashmapTestFunctions<Foo*, int32_t>::TestHashmapRemove(keyvaluePairFooPtr1, keyvaluePairFooPtr2, keyvaluePairFooPtr3);
		}

		TEST_METHOD(Hashmap_Clear)
		{
			// ---------------------- int32_t, int32_t ---------------------------
			int32_t key1 = 10;
			int32_t key2 = 20;
			int32_t key3 = 30;
			int32_t value1 = 100;
			int32_t value2 = 200;
			int32_t value3 = 1300;
			std::pair<int32_t, int32_t> keyvaluePair1(key1, value1);
			std::pair<int32_t, int32_t> keyvaluePair2(key2, value2);
			std::pair<int32_t, int32_t> keyvaluePair3(key3, value3);
			HashmapTestFunctions<int32_t, int32_t>::TestHashmapClear(keyvaluePair1, keyvaluePair2, keyvaluePair3);

			// ---------------------- int32_t*, int32_t ---------------------------
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr1(&key1, value1);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr2(&key2, value2);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr3(&key3, value3);
			HashmapTestFunctions<int32_t*, int32_t>::TestHashmapClear(keyvaluePairIntPtr1, keyvaluePairIntPtr2, keyvaluePairIntPtr3);

			// ---------------------- char*, int32_t ---------------------------
			char* str1 = "Alpha";
			char* str2 = "Charlie";
			char* str3 = "Delta";
			std::pair<char*, int32_t> keyvaluePairCharPtr1(str1, value1);
			std::pair<char*, int32_t> keyvaluePairCharPtr2(str2, value2);
			std::pair<char*, int32_t> keyvaluePairCharPtr3(str3, value3);
			HashmapTestFunctions<char*, int32_t>::TestHashmapClear(keyvaluePairCharPtr1, keyvaluePairCharPtr2, keyvaluePairCharPtr3);

			// ---------------------- std::String, int32_t ---------------------------
			std::pair<std::string, int32_t> keyvaluePairString1(std::string(str1), value1);
			std::pair<std::string, int32_t> keyvaluePairString2(std::string(str2), value2);
			std::pair<std::string, int32_t> keyvaluePairString3(std::string(str3), value3);
			HashmapTestFunctions<std::string, int32_t>::TestHashmapClear(keyvaluePairString1, keyvaluePairString2, keyvaluePairString3);

			// ---------------------- Foo, int32_t ---------------------------
			Foo fooObj1(key1);
			Foo fooObj2(key2);
			Foo fooObj3(key3);
			std::pair<Foo, int32_t> keyvaluePairFoo1(fooObj1, value1);
			std::pair<Foo, int32_t> keyvaluePairFoo2(fooObj2, value2);
			std::pair<Foo, int32_t> keyvaluePairFoo3(fooObj3, value3);
			HashmapTestFunctions<Foo, int32_t, FooHashFunction>::TestHashmapClear(keyvaluePairFoo1, keyvaluePairFoo2, keyvaluePairFoo3);

			// ---------------------- Foo*, int32_t ---------------------------
			std::pair<Foo*, int32_t> keyvaluePairFooPtr1(&fooObj1, value1);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr2(&fooObj2, value2);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr3(&fooObj3, value3);
			HashmapTestFunctions<Foo*, int32_t>::TestHashmapClear(keyvaluePairFooPtr1, keyvaluePairFooPtr2, keyvaluePairFooPtr3);
		}

		TEST_METHOD(Hashmap_Bracket_Operator)
		{
			// ---------------------- int32_t, int32_t ---------------------------
			int32_t key1 = 10;
			int32_t key2 = 20;
			int32_t key3 = 30;
			int32_t value1 = 100;
			int32_t value2 = 200;
			int32_t value3 = 1300;
			std::pair<int32_t, int32_t> keyvaluePair1(key1, value1);
			std::pair<int32_t, int32_t> keyvaluePair2(key2, value2);
			std::pair<int32_t, int32_t> keyvaluePair3(key3, value3);
			HashmapTestFunctions<int32_t, int32_t>::TestHashmapBracketOperator(keyvaluePair1, keyvaluePair2, keyvaluePair3);

			// ---------------------- int32_t*, int32_t ---------------------------
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr1(&key1, value1);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr2(&key2, value2);
			std::pair<int32_t*, int32_t> keyvaluePairIntPtr3(&key3, value3);
			HashmapTestFunctions<int32_t*, int32_t>::TestHashmapBracketOperator(keyvaluePairIntPtr1, keyvaluePairIntPtr2, keyvaluePairIntPtr3);

			// ---------------------- char*, int32_t ---------------------------
			char* str1 = "Alpha";
			char* str2 = "Charlie";
			char* str3 = "Delta";
			std::pair<char*, int32_t> keyvaluePairCharPtr1(str1, value1);
			std::pair<char*, int32_t> keyvaluePairCharPtr2(str2, value2);
			std::pair<char*, int32_t> keyvaluePairCharPtr3(str3, value3);
			HashmapTestFunctions<char*, int32_t>::TestHashmapBracketOperator(keyvaluePairCharPtr1, keyvaluePairCharPtr2, keyvaluePairCharPtr3);

			// ---------------------- std::String, int32_t ---------------------------
			std::pair<std::string, int32_t> keyvaluePairString1(std::string(str1), value1);
			std::pair<std::string, int32_t> keyvaluePairString2(std::string(str2), value2);
			std::pair<std::string, int32_t> keyvaluePairString3(std::string(str3), value3);
			HashmapTestFunctions<std::string, int32_t>::TestHashmapBracketOperator(keyvaluePairString1, keyvaluePairString2, keyvaluePairString3);

			// ---------------------- Foo, int32_t ---------------------------
			Foo fooObj1(key1);
			Foo fooObj2(key2);
			Foo fooObj3(key3);
			std::pair<Foo, int32_t> keyvaluePairFoo1(fooObj1, value1);
			std::pair<Foo, int32_t> keyvaluePairFoo2(fooObj2, value2);
			std::pair<Foo, int32_t> keyvaluePairFoo3(fooObj3, value3);
			HashmapTestFunctions<Foo, int32_t, FooHashFunction>::TestHashmapBracketOperator(keyvaluePairFoo1, keyvaluePairFoo2, keyvaluePairFoo3);

			// ---------------------- Foo*, int32_t ---------------------------
			std::pair<Foo*, int32_t> keyvaluePairFooPtr1(&fooObj1, value1);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr2(&fooObj2, value2);
			std::pair<Foo*, int32_t> keyvaluePairFooPtr3(&fooObj3, value3);
			HashmapTestFunctions<Foo*, int32_t>::TestHashmapBracketOperator(keyvaluePairFooPtr1, keyvaluePairFooPtr2, keyvaluePairFooPtr3);
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashmapTest::sStartMemState;
}