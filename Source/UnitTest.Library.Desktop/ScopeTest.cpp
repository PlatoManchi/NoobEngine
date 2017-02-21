#include "pch.h"
#include "CppUnitTest.h"
#include "Runtime/Scope.h"
#include "Runtime/Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NoobEngine::Runtime;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> std::wstring ToString<DatumType>(const DatumType& pType)
			{
				std::wstringstream stringStream;
				switch (pType)
				{
				case NoobEngine::Runtime::DatumType::INTEGER:
					stringStream << "DatumType::INTEGER";
					break;
				case NoobEngine::Runtime::DatumType::FLOAT:
					stringStream << "DatumType::FLOAT";
					break;
				case NoobEngine::Runtime::DatumType::STRING:
					stringStream << "DatumType::STRING";
					break;
				case NoobEngine::Runtime::DatumType::VECTOR_4:
					stringStream << "DatumType::VECTOR_4";
					break;
				case NoobEngine::Runtime::DatumType::MATRIX_4x4:
					stringStream << "DatumType::MATRIX_4x4";
					break;
				case NoobEngine::Runtime::DatumType::RTTI_TYPE:
					stringStream << "DatumType::RTTI_TYPE";
					break;
				case NoobEngine::Runtime::DatumType::UNASSIGNED:
					stringStream << "DatumType::UNASSIGNED";
					break;
				default:
					stringStream << "INVALID DatumType";
					break;
				}

				std::wstring copyOfStr = stringStream.str();

				return copyOfStr;
			}
		}
	}
}

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(ScopeTest)
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

		TEST_METHOD(Scope_Constructor)
		{
			Scope tmpScope;

			Assert::IsTrue(tmpScope.GetParent() == nullptr);
		}

		TEST_METHOD(Scope_Append)
		{
			Scope tmpScope;

			std::string key1 = "Name";
			std::string key2 = "Height";

			Datum& key1Datum = tmpScope.Append(key1);
			Assert::AreEqual(key1Datum.Type(), DatumType::UNASSIGNED);
			tmpScope.Append(key1) = "Plato";
			Assert::AreEqual(key1Datum.Type(), DatumType::STRING);

			tmpScope.Append(key2) = "Alpha";
			Assert::AreEqual(tmpScope.Append(key2).Type(), DatumType::STRING);
		}

		TEST_METHOD(Scope_Find)
		{
			Scope tmpScope;

			std::string key1 = "Name";
			std::string key2 = "Height";

			Assert::IsTrue(tmpScope.Find(key1) == nullptr);

			tmpScope.Append(key1);

			Assert::IsTrue(tmpScope.Find(key1) != nullptr);
			Assert::IsTrue(tmpScope.Find(key2) == nullptr);
		}

		TEST_METHOD(Scope_AppendScope)
		{
			Scope parentScope;
			std::string parentKey1 = "Name";
			std::string parentKey2 = "Height";
			std::string parentKey3 = "Powers";

			parentScope.Append(parentKey1) = "Plato";
			parentScope.Append(parentKey2) = 5.10f;

			Assert::IsTrue(parentScope.Find(parentKey3) == nullptr);
			
			parentScope.AppendScope(parentKey3);

			Assert::IsTrue(parentScope.Find(parentKey3) != nullptr);

			Scope* childScope1Find = parentScope.Find(parentKey3)->Get<Scope*>(0);

			std::string childKey1 = "Name";
			std::string childKey2 = "Damage";

			Assert::IsTrue(parentScope.Find(parentKey3)->Get<Scope*>(0)->Find(childKey1) == nullptr);

			childScope1Find->Append(childKey1) = "Fire";
			childScope1Find->Append(childKey2) = 20.0f;

			Assert::IsTrue(parentScope.Find(parentKey3)->Get<Scope*>(0)->Find(childKey1) != nullptr);
			Assert::IsTrue(parentScope.Find(parentKey3)->Get<Scope*>(0)->Find(childKey2) != nullptr);
		}

		TEST_METHOD(Scope_Search)
		{
			Scope playerScope;
			Scope* foundScope;
			std::string parentKey1 = "Name";
			std::string parentKey2 = "Health";
			std::string parentKey3 = "Powers";

			Assert::IsTrue(playerScope.Search(parentKey1, &foundScope) == nullptr);

			playerScope.Append(parentKey1) = "Plato";
			playerScope.Append(parentKey2) = 100.0f;

			Assert::IsTrue(playerScope.Search(parentKey1, &foundScope) != nullptr);
			Assert::IsTrue(&playerScope == foundScope);

			// adding power scope
			playerScope.AppendScope(parentKey3);

			std::string powerKey1 = "Name";
			std::string powerKey2 = "Damage";

			
			(*playerScope.Find(parentKey3))[0]->Append(powerKey1) = "PyroAttack";
			(*playerScope.Find(parentKey3))[0]->AppendScope(powerKey2);
			
			Scope pyroattackScope;
			
			std::string damageKey1 = "Type";
			std::string damageKey2 = "Value";

			(*(*playerScope.Find(parentKey3))[0]->Find(powerKey2))[0]->Append(damageKey1) = "Fire";
			(*(*playerScope.Find(parentKey3))[0]->Find(powerKey2))[0]->Append(damageKey2) = 50.0f;

			Scope* powerScope = (*(*playerScope.Find(parentKey3))[0]->Find(powerKey2))[0];
			Assert::IsTrue(powerScope->Search(parentKey1, &foundScope) != nullptr);
			Assert::IsTrue((*playerScope.Find(parentKey3))[0] == foundScope);
		}

		TEST_METHOD(Scope_FindName)
		{
			Scope playerScope;
			
			std::string parentKey1 = "Name";
			std::string parentKey2 = "Health";
			std::string parentKey3 = "Powers";

			playerScope.Append(parentKey1) = "Plato";
			playerScope.Append(parentKey2) = 100.0f;

			// adding power scope
			Scope& powerScope = playerScope.AppendScope(parentKey3);
			Scope tmpRandomScope;

			Assert::AreEqual(std::string(""), tmpRandomScope.FindName(powerScope));
			Assert::AreEqual(parentKey3, playerScope.FindName(powerScope));
		}

		TEST_METHOD(Scope_GetParent)
		{
			Scope playerScope;

			std::string parentKey1 = "Name";
			std::string parentKey2 = "Health";
			std::string parentKey3 = "Powers";

			playerScope.Append(parentKey1) = "Plato";
			playerScope.Append(parentKey2) = 100.0f;

			// adding power scope
			Scope& powerScope = playerScope.AppendScope(parentKey3);

			Assert::IsTrue(nullptr == playerScope.GetParent());
			Assert::IsTrue(&playerScope == powerScope.GetParent());
		}

		TEST_METHOD(Scope_ToString)
		{
			Scope playerScope;

			Assert::AreEqual(std::string("Scope"), playerScope.ToString());
		}

		TEST_METHOD(Scope_Adopt)
		{
			std::string parentKey1 = "Name";
			std::string parentKey2 = "Health";
			std::string parentKey3 = "Powers";

			std::string powerKey1 = "Name";
			std::string powerKey2 = "Damage";

			Scope playerScope1;
			
			playerScope1.Append(parentKey1) = "Plato";
			playerScope1.Append(parentKey2) = 100.0f;

			// adding power scope
			playerScope1.AppendScope(parentKey3);

			(*playerScope1.Find(parentKey3))[0]->Append(powerKey1) = "PyroAttack";
			(*playerScope1.Find(parentKey3))[0]->Append(powerKey2) = 50.0f;

			// adding another scope
			playerScope1.AppendScope(parentKey3);

			(*playerScope1.Find(parentKey3))[0]->Append(powerKey1) = "FreezeAttack";
			(*playerScope1.Find(parentKey3))[0]->Append(powerKey2) = 50.0f;


			Scope* powerScope = (*playerScope1.Find(parentKey3))[0];
			Assert::IsTrue(powerScope->GetParent() == &playerScope1);

			// player 2
			Scope playerScope2;

			playerScope2.Append(parentKey1) = "Plato";
			playerScope2.Append(parentKey2) = 100.0f;

			playerScope2.Adopt(*powerScope, parentKey3);
			Assert::IsTrue(powerScope->GetParent() == &playerScope2);

			Assert::IsTrue("" == playerScope1.FindName(*powerScope));
			Assert::IsTrue("Powers" == playerScope2.FindName(*powerScope));
		}

		TEST_METHOD(Scope_ComparisonOperator)
		{
			std::string parentKey1 = "Name";
			std::string parentKey2 = "Health";
			std::string parentKey3 = "Powers";

			std::string powerKey1 = "Name";
			std::string powerKey2 = "Damage";

			Scope playerScope1;

			playerScope1.Append(parentKey1) = "Plato";
			playerScope1.Append(parentKey2) = 100.0f;
			// adding power scope
			playerScope1.AppendScope(parentKey3);

			(*playerScope1.Find(parentKey3))[0]->Append(powerKey1) = "PyroAttack";
			(*playerScope1.Find(parentKey3))[0]->Append(powerKey2) = 50.0f;

			// adding another scope
			playerScope1.AppendScope(parentKey3);

			(*playerScope1.Find(parentKey3))[0]->Append(powerKey1) = "FreezeAttack";
			(*playerScope1.Find(parentKey3))[0]->Append(powerKey2) = 50.0f;


			Scope playerScope2;

			playerScope2.Append(parentKey1) = "Plato";
			playerScope2.Append(parentKey2) = 100.0f;
			// adding power scope
			playerScope2.AppendScope(parentKey3);

			(*playerScope2.Find(parentKey3))[0]->Append(powerKey1) = "PyroAttack";
			(*playerScope2.Find(parentKey3))[0]->Append(powerKey2) = 50.0f;

			Assert::IsTrue(playerScope1 != playerScope2);

			// adding another scope
			playerScope2.AppendScope(parentKey3);

			(*playerScope2.Find(parentKey3))[0]->Append(powerKey1) = "FreezeAttack";
			(*playerScope2.Find(parentKey3))[0]->Append(powerKey2) = 50.0f;


			Assert::IsTrue(playerScope1 == playerScope1);
			Assert::IsTrue(playerScope1 == playerScope2);

			(*playerScope2.Find(parentKey3))[0]->Append(powerKey2) = 60.0f;
			Assert::IsFalse(playerScope1 == playerScope2);
		}

		TEST_METHOD(Scope_CopyConstructor)
		{
			std::string parentKey1 = "Name";
			std::string parentKey2 = "Health";
			std::string parentKey3 = "Powers";

			std::string powerKey1 = "Name";
			std::string powerKey2 = "Damage";

			Scope playerScope1;

			playerScope1.Append(parentKey1) = "Plato";
			playerScope1.Append(parentKey2) = 100.0f;
			
			// adding power scope
			playerScope1.AppendScope(parentKey3);
			(*playerScope1.Find(parentKey3))[0]->Append(powerKey1) = "PyroAttack";
			(*playerScope1.Find(parentKey3))[0]->Append(powerKey2) = 50.0f;

			// adding another scope
			playerScope1.AppendScope(parentKey3);
			(*playerScope1.Find(parentKey3))[1]->Append(powerKey1) = "FreezeAttack";
			(*playerScope1.Find(parentKey3))[1]->Append(powerKey2) = 50.0f;

			Scope playerScope2(playerScope1);
			
			Assert::IsTrue(playerScope1 == playerScope2);
		}

		TEST_METHOD(Scope_Equals)
		{
			std::string parentKey1 = "Name";
			std::string parentKey2 = "Health";
			std::string parentKey3 = "Powers";

			std::string powerKey1 = "Name";
			std::string powerKey2 = "Damage";

			Scope playerScope1;

			playerScope1.Append(parentKey1) = "Plato";
			playerScope1.Append(parentKey2) = 100.0f;

			// adding power scope
			playerScope1.AppendScope(parentKey3);
			(*playerScope1.Find(parentKey3))[0]->Append(powerKey1) = "PyroAttack";
			(*playerScope1.Find(parentKey3))[0]->Append(powerKey2) = 50.0f;

			// adding another scope
			playerScope1.AppendScope(parentKey3);
			(*playerScope1.Find(parentKey3))[1]->Append(powerKey1) = "FreezeAttack";
			(*playerScope1.Find(parentKey3))[1]->Append(powerKey2) = 50.0f;

			Scope playerScope2(playerScope1);

			RTTI* playerScope1RTTI = static_cast<RTTI*>(&playerScope1);

			Assert::IsTrue(playerScope1.Equals(playerScope1RTTI));
			Assert::IsFalse(playerScope1.Equals(nullptr));
			Assert::IsTrue(playerScope2.Equals(playerScope1RTTI));
		}

		TEST_METHOD(Scope_BracketOperator)
		{
			std::string parentKey1 = "Name";
			std::string parentKey2 = "Health";
			
			Scope playerScope;

			playerScope[parentKey1] = "Plato";
			playerScope[parentKey2] = 100.0f;

			uint32_t index = 0u;
			
			Assert::AreEqual(std::string("Plato"), playerScope[index++].Get<std::string>(0));
			Assert::AreEqual(100.0f, playerScope[index++].Get<float>(0));
			Assert::ExpectException<std::exception>([&] { playerScope[index]; });
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ScopeTest::sStartMemState;
}