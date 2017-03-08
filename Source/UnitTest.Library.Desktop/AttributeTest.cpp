#include "pch.h"
#include "CppUnitTest.h"
#include "SupportingClasses/FooAttribute.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SupportingClasses;
using namespace NoobEngine::Runtime;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(AttributeTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			//FooAttribute fAttrib1;
			//

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

		TEST_METHOD(DefaultConstructor)
		{
			FooAttribute fAttrib1;
			/*Assert::IsTrue(fAttrib1.IsAttribute("Name"));

			Assert::AreEqual(100, fAttrib1["Health"].Get<int>());

			fAttrib1.mHealth = 50;

			Assert::AreEqual(50, fAttrib1["Health"].Get<int>());

			fAttrib1["Health"] = 10;

			Assert::AreEqual(10, fAttrib1.mHealth);*/
		}

		TEST_METHOD(IsAttribute)
		{
			FooAttribute fAttrib1;

			Assert::IsTrue(fAttrib1.IsAttribute("this"));
			Assert::IsTrue(fAttrib1.IsAttribute("Name"));
			Assert::IsTrue(fAttrib1.IsAttribute("Health"));
			Assert::IsTrue(fAttrib1.IsAttribute("Regen"));
			Assert::IsTrue(fAttrib1.IsAttribute("Pos"));

			Assert::IsFalse(fAttrib1.IsAttribute("Random"));
		}

		TEST_METHOD(AppendAuxiliaryAttribute)
		{
			FooAttribute fAttrib1;

			float armor = 10.0f;

			fAttrib1.AppendAuxiliaryAttribute("Armor") = armor;

			Assert::AreEqual(armor, fAttrib1["Armor"].Get<float>());
			Assert::AreNotEqual(&armor, &fAttrib1["Armor"].Get<float>());

			Assert::ExpectException<std::exception>([&] { fAttrib1.AppendAuxiliaryAttribute("Name"); });
		}

		TEST_METHOD(AppendPrescribedAttribute)
		{
			FooAttribute fAttrib1;

			Assert::IsTrue(&fAttrib1.mName == &fAttrib1["Name"].Get<std::string>());
			Assert::IsTrue(&fAttrib1.mHealth == &fAttrib1["Health"].Get<int>());
			Assert::IsTrue(&fAttrib1.mRegen == &fAttrib1["Regen"].Get<float>());
			Assert::IsTrue(&fAttrib1.mPos == &fAttrib1["Pos"].Get<glm::vec4>());
			Assert::IsTrue(&fAttrib1 == fAttrib1["this"].Get<NoobEngine::Runtime::RTTI*>());

			fAttrib1.mName = "Plato";
			Assert::AreEqual(fAttrib1.mName, fAttrib1["Name"].Get<std::string>());

			Assert::ExpectException<std::exception>([&] { fAttrib1.ExceptionAddingPrescribed(); });
		}

		TEST_METHOD(IsPrescribedAttribute)
		{
			FooAttribute fAttrib1;
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("this"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Name"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Health"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Regen"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Pos"));

			fAttrib1.AppendAuxiliaryAttribute("Aux") = 10;

			Assert::IsFalse(fAttrib1.IsPrescribedAttribute("Aux"));
			Assert::IsFalse(fAttrib1.IsPrescribedAttribute("Plato"));
		}

		TEST_METHOD(IsAuxiliaryAttribute)
		{
			FooAttribute fAttrib1;
			fAttrib1.AppendAuxiliaryAttribute("Aux") = 10;

			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("Aux"));
			Assert::IsFalse(fAttrib1.IsAuxiliaryAttribute("Plato"));
		}

		TEST_METHOD(CopyConstructor)
		{
			FooAttribute fAttrib1;
			fAttrib1.mName = "Plato";
			int aux = 10;
			fAttrib1.AppendAuxiliaryAttribute("Aux") = aux;

			FooAttribute fAttrib2(fAttrib1);

			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("this"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Name"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Health"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Regen"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Pos"));

			Assert::IsTrue(&fAttrib1.mName == &fAttrib1["Name"].Get<std::string>());
			Assert::IsTrue(&fAttrib1.mHealth == &fAttrib1["Health"].Get<int>());
			Assert::IsTrue(&fAttrib1.mRegen == &fAttrib1["Regen"].Get<float>());
			Assert::IsTrue(&fAttrib1.mPos == &fAttrib1["Pos"].Get<glm::vec4>());
			Assert::IsTrue(&fAttrib1 == fAttrib1["this"].Get<NoobEngine::Runtime::RTTI*>());

			Assert::IsTrue(&fAttrib2.mName == &fAttrib2["Name"].Get<std::string>());
			Assert::IsTrue(&fAttrib2.mHealth == &fAttrib2["Health"].Get<int>());
			Assert::IsTrue(&fAttrib2.mRegen == &fAttrib2["Regen"].Get<float>());
			Assert::IsTrue(&fAttrib2.mPos == &fAttrib2["Pos"].Get<glm::vec4>());
			Assert::IsTrue(&fAttrib2 == fAttrib2["this"].Get<RTTI*>());

			Assert::AreEqual(fAttrib1["Name"].Get<std::string>(), fAttrib2["Name"].Get<std::string>());
			Assert::AreEqual(fAttrib1["Health"].Get<int>(), fAttrib2["Health"].Get<int>());
			Assert::AreEqual(fAttrib1["Regen"].Get<float>(), fAttrib2["Regen"].Get<float>());
			Assert::IsTrue(fAttrib1["Pos"].Get<glm::vec4>() == fAttrib2["Pos"].Get<glm::vec4>());

			Assert::IsTrue(fAttrib2.IsAuxiliaryAttribute("Aux"));
			Assert::AreEqual(aux, fAttrib2["Aux"].Get<int>());

			Assert::IsFalse(&fAttrib1["Name"].Get<std::string>() == &fAttrib2["Name"].Get<std::string>());
			Assert::IsFalse(&fAttrib1["Health"].Get<int>() == &fAttrib2["Health"].Get<int>());
			Assert::IsFalse(&fAttrib1["Regen"].Get<float>() == &fAttrib2["Regen"].Get<float>());
			Assert::IsFalse(&fAttrib1["Pos"].Get<glm::vec4>() == &fAttrib2["Pos"].Get<glm::vec4>());
			Assert::IsFalse(&fAttrib1["this"].Get<RTTI*>() == &fAttrib2["this"].Get<RTTI*>());
		}

		TEST_METHOD(AssignmentOperator)
		{
			FooAttribute fAttrib1;
			fAttrib1.mName = "Plato";
			int aux = 10;
			fAttrib1.AppendAuxiliaryAttribute("Aux") = aux;

			FooAttribute fAttrib2;

			fAttrib2 = fAttrib1;

			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("this"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Name"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Health"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Regen"));
			Assert::IsTrue(fAttrib1.IsPrescribedAttribute("Pos"));

			Assert::IsTrue(&fAttrib1.mName == &fAttrib1["Name"].Get<std::string>());
			Assert::IsTrue(&fAttrib1.mHealth == &fAttrib1["Health"].Get<int>());
			Assert::IsTrue(&fAttrib1.mRegen == &fAttrib1["Regen"].Get<float>());
			Assert::IsTrue(&fAttrib1.mPos == &fAttrib1["Pos"].Get<glm::vec4>());
			Assert::IsTrue(&fAttrib1 == fAttrib1["this"].Get<NoobEngine::Runtime::RTTI*>());

			Assert::IsTrue(&fAttrib2.mName == &fAttrib2["Name"].Get<std::string>());
			Assert::IsTrue(&fAttrib2.mHealth == &fAttrib2["Health"].Get<int>());
			Assert::IsTrue(&fAttrib2.mRegen == &fAttrib2["Regen"].Get<float>());
			Assert::IsTrue(&fAttrib2.mPos == &fAttrib2["Pos"].Get<glm::vec4>());
			Assert::IsTrue(&fAttrib2 == fAttrib2["this"].Get<RTTI*>());

			Assert::AreEqual(fAttrib1["Name"].Get<std::string>(), fAttrib2["Name"].Get<std::string>());
			Assert::AreEqual(fAttrib1["Health"].Get<int>(), fAttrib2["Health"].Get<int>());
			Assert::AreEqual(fAttrib1["Regen"].Get<float>(), fAttrib2["Regen"].Get<float>());
			Assert::IsTrue(fAttrib1["Pos"].Get<glm::vec4>() == fAttrib2["Pos"].Get<glm::vec4>());

			Assert::IsTrue(fAttrib2.IsAuxiliaryAttribute("Aux"));
			Assert::AreEqual(aux, fAttrib2["Aux"].Get<int>());

			Assert::IsFalse(&fAttrib1["Name"].Get<std::string>() == &fAttrib2["Name"].Get<std::string>());
			Assert::IsFalse(&fAttrib1["Health"].Get<int>() == &fAttrib2["Health"].Get<int>());
			Assert::IsFalse(&fAttrib1["Regen"].Get<float>() == &fAttrib2["Regen"].Get<float>());
			Assert::IsFalse(&fAttrib1["Pos"].Get<glm::vec4>() == &fAttrib2["Pos"].Get<glm::vec4>());
			Assert::IsFalse(&fAttrib1["this"].Get<RTTI*>() == &fAttrib2["this"].Get<RTTI*>());
		}

		TEST_METHOD(AppendNestedScope)
		{
			FooAttribute fAttrib1;

			Scope *s = new Scope();

			fAttrib1.AppendNestedScope("scope", *s);

			Assert::ExpectException<std::exception>([&] { fAttrib1.AppendNestedScope("scope", *s); });
		}

		TEST_METHOD(AddInternalAttribute)
		{
			FooAttribute fAttrib1;

			int initialInt = 10;
			float initialFlaot = 10.0f;
			std::string initialStr = "";
			glm::vec4 initialVec4 = glm::vec4();
			glm::mat4x4 initalMat4x4 = glm::mat4x4();
			
			fAttrib1.AddInternalAttribute("InternalInt", initialInt);
			fAttrib1.AddInternalAttribute("InternalFloat", initialFlaot);
			fAttrib1.AddInternalAttribute("InternalString", initialStr);
			fAttrib1.AddInternalAttribute("InternalVec4", initialVec4);
			fAttrib1.AddInternalAttribute("InternalMat4x4", initalMat4x4);
			fAttrib1.AddInternalAttribute("InternalRTTI", nullptr);

			Assert::IsTrue(fAttrib1.IsAttribute("InternalInt"));
			Assert::IsTrue(fAttrib1.IsAttribute("InternalFloat"));
			Assert::IsTrue(fAttrib1.IsAttribute("InternalString"));
			Assert::IsTrue(fAttrib1.IsAttribute("InternalVec4"));
			Assert::IsTrue(fAttrib1.IsAttribute("InternalMat4x4"));
			Assert::IsTrue(fAttrib1.IsAttribute("InternalRTTI"));

			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalInt"));
			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalFloat"));
			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalString"));
			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalVec4"));
			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalMat4x4"));
			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalRTTI"));
		}

		TEST_METHOD(AddExternalAttribute)
		{
			FooAttribute fAttrib1;

			int initialInt = 10;
			float initialFlaot = 10.0f;
			std::string initialStr = "";
			glm::vec4 initialVec4 = glm::vec4();
			glm::mat4x4 initalMat4x4 = glm::mat4x4();
			RTTI *s = new Scope();

			fAttrib1.AddExternalAttribute("InternalInt", &initialInt);
			fAttrib1.AddExternalAttribute("InternalFloat", &initialFlaot);
			fAttrib1.AddExternalAttribute("InternalString", &initialStr);
			fAttrib1.AddExternalAttribute("InternalVec4", &initialVec4);
			fAttrib1.AddExternalAttribute("InternalMat4x4", &initalMat4x4);
			fAttrib1.AddExternalAttribute("InternalRTTI", &s);

			Assert::IsTrue(fAttrib1.IsAttribute("InternalInt"));
			Assert::IsTrue(fAttrib1.IsAttribute("InternalFloat"));
			Assert::IsTrue(fAttrib1.IsAttribute("InternalString"));
			Assert::IsTrue(fAttrib1.IsAttribute("InternalVec4"));
			Assert::IsTrue(fAttrib1.IsAttribute("InternalMat4x4"));
			Assert::IsTrue(fAttrib1.IsAttribute("InternalRTTI"));

			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalInt"));
			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalFloat"));
			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalString"));
			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalVec4"));
			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalMat4x4"));
			Assert::IsTrue(fAttrib1.IsAuxiliaryAttribute("InternalRTTI"));

			delete(s);
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributeTest::sStartMemState;
}