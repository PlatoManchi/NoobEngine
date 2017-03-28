#include "pch.h"
#include "CppUnitTest.h"
#include "SupportingClasses/ProductFoo.h"
#include "SupportingClasses/ProductBar.h"
#include "SupportingClasses/NonRTTIProduct.h"
#include "SupportingClasses/FactoryFooFactoryT.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SupportingClasses;
using namespace NoobEngine::Generic;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(FactoryTest)
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

		TEST_METHOD(AddRemoveTest)
		{
			ProductFoo factoryFoo;
			ProductFooFactory fooFactory;

			NoobEngine::Runtime::RTTI* fooPtr = fooFactory.Create();
			Assert::IsTrue(fooPtr != nullptr);
			Assert::IsTrue(fooPtr->Is(ProductFoo::TypeIdClass()));

			{
				ProductBar factoryBar;
				ProductBarFactory barFactory;

				NoobEngine::Runtime::RTTI* barPtr = Factory<NoobEngine::Runtime::RTTI>::Create(barFactory.ClassName());
				Assert::IsTrue(barPtr != nullptr);

				delete barPtr;
			}

			delete fooPtr;

			fooPtr = Factory<NoobEngine::Runtime::RTTI>::Create("ProductFoo");
			Assert::IsTrue(fooPtr != nullptr);
			delete fooPtr;

			// when bar factory got out of scope it will remove itself from factories list
			NoobEngine::Runtime::RTTI* barPtr = Factory<NoobEngine::Runtime::RTTI>::Create("ProductBar");
			Assert::IsTrue(barPtr == nullptr);
		}

		TEST_METHOD(NonRTTIProductTest)
		{
			NonRTTIProduct nonRTTITest;
			NonRTTIProductFactory factory;

			IProduct* ptr = factory.Create();
			Assert::IsTrue(ptr != nullptr);
			
			delete ptr;
		}

		TEST_METHOD(FindTest)
		{
			ProductFooFactory fooFactory;

			Factory<NoobEngine::Runtime::RTTI>* foundFactory = fooFactory.Find("");

			Assert::IsTrue(nullptr == foundFactory);

			foundFactory = fooFactory.Find(fooFactory.ClassName());

			Assert::IsTrue(&fooFactory == foundFactory);
		}

		TEST_METHOD(IteratorTest)
		{
			int count = 0;

			NonRTTIProductFactory factory;

			for (auto element : factory)
			{
				count++;
			}

			Assert::AreEqual(1, count);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState FactoryTest::sStartMemState;
}