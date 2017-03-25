#include "pch.h"
#include "CppUnitTest.h"
#include "Runtime/Datum.h"
#include "../../External/glm/glm/vec4.hpp"
#include "../../External/glm/glm/mat4x4.hpp"
#include "SupportingClasses/Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NoobEngine::Runtime;
using namespace SupportingClasses;

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
	template<typename T, typename OtherType = int32_t, typename InvalidType = Foo>
	class DatumTestFunctions
	{
	public:
		static void TestDefaultConstructor()
		{
			Datum d;
			Assert::AreEqual(0U, d.Size());
			Assert::AreEqual(DatumType::UNASSIGNED, d.Type());
			Assert::ExpectException<std::exception>([&] { d.Get<int32_t>(); });
		}

		static void TestSetType(DatumType pType1, DatumType pErrorType)
		{
			Datum d;
			Assert::AreEqual(0U, d.Size());
			Assert::AreEqual(DatumType::UNASSIGNED, d.Type());
			
			d.SetType(pType1);
			Assert::AreEqual(pType1, d.Type());
			Assert::ExpectException<std::exception>([&] { d.SetType(pErrorType); });
		}

		static void TestSetSize(DatumType pType)
		{
			Datum d;
			Assert::AreEqual(0U, d.Size());
			Assert::AreEqual(DatumType::UNASSIGNED, d.Type());
			Assert::ExpectException<std::exception>([&] { d.SetSize(10U); });

			d.SetType(pType);
			Assert::AreEqual(pType, d.Type());
			d.SetSize(10U);
			Assert::AreEqual(10U, d.Size());

			d.PushBack(10);
			d.PushBack(20);
			d.PushBack(30);
			d.PushBack(40);

			d.SetSize(2U);
			Assert::AreEqual(2U, d.Size());
		}

		static void TestPushBack(DatumType pCorrectType, T pValue1, T pValue2, T pValue3, OtherType pErrorValue)
		{
			Datum d;
			Assert::AreEqual(0U, d.Size());
			Assert::AreEqual(DatumType::UNASSIGNED, d.Type());

			d.PushBack(pValue1);
			Assert::AreEqual(1U, d.Size());
			Assert::AreEqual(pCorrectType, d.Type());

			d.PushBack(pValue2);
			Assert::AreEqual(2U, d.Size());

			d.PushBack(pValue3);
			Assert::AreEqual(3U, d.Size());

			Assert::ExpectException<std::exception>([&] { d.PushBack(pErrorValue); });
		}

		static void TestPopBack(T pValue1, T pValue2)
		{
			Datum d;
			Assert::AreEqual(0U, d.Size());
			Assert::ExpectException<std::exception>([&] { d.PopBack(); });

			d.PushBack(pValue1);
			d.PushBack(pValue2);

			Assert::AreEqual(2U, d.Size());

			d.PopBack();
			Assert::AreEqual(1U, d.Size());

			d.PopBack();
			Assert::AreEqual(0U, d.Size());

			Assert::ExpectException<std::exception>([&] { d.PopBack(); });
		}

		static void TestClear(T pValue1, T pValue2)
		{
			Datum d;
			Assert::AreEqual(0U, d.Size());

			d.PushBack(pValue1);
			d.PushBack(pValue2);

			Assert::AreEqual(2U, d.Size());

			d.Clear();

			Assert::AreEqual(0U, d.Size());
		}

		static void TestSetStorage(DatumType pDatumType, T* pValueArr, uint32_t pArrSize, OtherType* pErrorArr, uint32_t pErrorSize)
		{
			
			Datum d;
			Assert::AreEqual(0U, d.Size());

			//Assert::ExpectException<std::exception>([&] { d.SetStorage(pValueArr, pArrSize); });

			d.SetType(pDatumType);

			d.SetStorage(pValueArr, pArrSize);

			Assert::AreEqual(pArrSize, d.Size());

			Assert::ExpectException<std::exception>([&] { d.SetStorage(pErrorArr, pErrorSize); });

			// getting code coverage in PopBack for external storage.
			d.PopBack();

			// getting code coverage in PushBack for external storage
			Assert::ExpectException<std::exception>([&] { d.PushBack(pValueArr[0]); });

			// getting code coverage in SetSize for external storage
			Assert::ExpectException<std::exception>([&] { d.SetSize(10U); });
		}

		static void TestComparisonOperator(T pValue1, T pValue2, T pValue3)
		{
			Datum d1;
			Datum d2;

			Assert::IsTrue(d1 == d1);
			Assert::IsTrue(d1 == d2);
			Assert::IsFalse(d1 != d2);

			d1.PushBack(pValue1);

			Assert::IsFalse(d1 == d2);

			d2.PushBack(pValue2);

			Assert::IsTrue(d1 != d2);

			d2.PopBack();
			d2.PushBack(pValue1);

			Assert::IsTrue(d1 == d2);

			d1.PushBack(pValue2);
			d1.PushBack(pValue3);

			Assert::IsFalse(d1 == d2);

			d2.PushBack(pValue2);
			d2.PushBack(pValue3);

			Assert::IsTrue(d1 == d2);
		}

		static void TestAssignmentOperator(DatumType pType, T pValue1, T pValue2, T pValue3, T* pArray, uint32_t pSize)
		{
			Datum d1;
			Datum d2;
			
			Assert::AreEqual(0U, d2.Size());
			Assert::AreEqual(DatumType::UNASSIGNED, d2.Type());

			d1.PushBack(pValue1);
			d1.PushBack(pValue2);

			d2 = d1;

			Assert::AreEqual(d1.Size(), d2.Size());
			Assert::AreEqual(pType, d2.Type());
			Assert::IsTrue(d1 == d2);

			d2 = pValue3;

			Assert::AreEqual(d1.Size(), d2.Size());
			Assert::AreEqual(pType, d2.Type());
			Assert::IsFalse(d1 == d2);

			// testing for external storage
			Datum d3;
			d3.SetType(pType);
			d3.SetStorage(pArray, pSize);

			d2 = d3;
			Assert::AreEqual(d2.Size(), pSize);
			Assert::AreEqual(pType, d2.Type());
			Assert::IsFalse(d1 == d3);
		}

		static void TestCopyConstructor(DatumType pType, T pValue1, T pValue2, T pValue3, T* pArray, uint32_t pSize)
		{
			Datum d1;
			
			Assert::AreEqual(0U, d1.Size());
			Assert::AreEqual(DatumType::UNASSIGNED, d1.Type());

			d1.PushBack(pValue1);
			d1.PushBack(pValue2);
			d1.PushBack(pValue3);

			Datum d2(d1);

			Assert::AreEqual(d1.Size(), d2.Size());
			Assert::AreEqual(pType, d2.Type());

			// testing for external storage
			Datum d3;
			d3.SetType(pType);
			d3.SetStorage(pArray, pSize);

			Datum d4(d3);
			Assert::AreEqual(d4.Size(), pSize);
			Assert::AreEqual(pType, d4.Type());
			Assert::IsTrue(d4 == d3);
		}

		static void TestGet(uint32_t pSize, T pValue1, T pValue2, T pValue3)
		{
			Datum d1;

			Assert::AreEqual(0U, d1.Size());
			Assert::AreEqual(DatumType::UNASSIGNED, d1.Type());
			Assert::ExpectException<std::exception>([&] { d1.Get<T>(); });

			d1.PushBack(pValue1);
			d1.PushBack(pValue2);
			d1.PushBack(pValue3);

			Assert::IsTrue(pValue1 == d1.Get<T>(0));
			Assert::IsTrue(pValue2 == d1.Get<T>(1));
			Assert::IsTrue(pValue3 == d1.Get<T>(2));
			Assert::ExpectException<std::exception>([&] { d1.Get<T>(pSize); });
			Assert::ExpectException<std::exception>([&] { d1.Get<InvalidType>(); });

			const Datum d2 = d1;

			Assert::IsTrue(pValue1 == d2.Get<T>(0));
			Assert::IsTrue(pValue2 == d2.Get<T>(1));
			Assert::IsTrue(pValue3 == d2.Get<T>(2));
			Assert::ExpectException<std::exception>([&] { d2.Get<T>(pSize); });
			Assert::ExpectException<std::exception>([&] { d2.Get<InvalidType>(); });
		}

		static void TestSet(T pValue1, T pValue2, T pValue3, OtherType pOtherTypeValue)
		{
			Datum d1;

			Assert::AreEqual(0U, d1.Size());
			Assert::AreEqual(DatumType::UNASSIGNED, d1.Type());
			Assert::ExpectException<std::exception>([&] { d1.Set(pValue1, 0); });

			d1.PushBack(pValue1);
			d1.PushBack(pValue2);

			Assert::IsTrue(pValue1 == d1.Get<T>(0));
			Assert::IsTrue(pValue2 == d1.Get<T>(1));

			d1.Set(pValue3, 0);
			Assert::IsTrue(pValue3 == d1.Get<T>(0));

			Assert::ExpectException<std::exception>([&] { d1.Set(pOtherTypeValue, 0); });
		}

		static void TestToString(T pValue)
		{
			Datum d1;
			Assert::ExpectException<std::exception>([&] { d1.ToString(0); });

			d1.PushBack(pValue);
			Assert::AreEqual(ToString(pValue), d1.ToString());
		}

		static void TestSetFromString(DatumType pType, T pValue1, std::string pStr1, T pValue2, std::string pStr2)
		{
			Datum d1;
			Assert::ExpectException<std::exception>([&] { d1.SetFromString(pStr1); });

			d1.SetType(pType);
			Assert::ExpectException<std::exception>([&] { d1.SetFromString(pStr1, 1); });

			d1.SetFromString(pStr1);

			Assert::AreEqual(pStr1, d1.ToString(0));
			Assert::IsTrue(pValue1 == d1.Get<T>(0));

			d1.SetFromString(pStr2);

			Assert::AreEqual(pStr2, d1.ToString(0));
			pValue2;
			Assert::IsTrue(pValue2 == d1.Get<T>(0));
		}
#pragma region Helper
		static std::string ToString(int32_t pValue)
		{
			std::ostringstream stringStream;
			stringStream << pValue;
			return stringStream.str();
		}

		static std::string ToString(float pValue)
		{
			std::ostringstream stringStream;
			stringStream << pValue;
			return stringStream.str();
		}

		static std::string ToString(std::string pValue)
		{
			return pValue;
		}

		static std::string ToString(glm::vec4 pValue)
		{
			std::ostringstream stringStream;
			stringStream << "{" << pValue.x << ", " << pValue.y << ", " << pValue.z << ", " << pValue.w << "}";
			return stringStream.str();
		}

		static std::string ToString(glm::mat4x4 pValue)
		{
			std::ostringstream stringStream;
			stringStream 
				<< "{{" << pValue[0].x << ", " << pValue[0].y << ", " << pValue[0].z << ", " << pValue[0].w << "}, "
				<< "{" << pValue[1].x << ", " << pValue[1].y << ", " << pValue[1].z << ", " << pValue[1].w << "}, "
				<< "{" << pValue[2].x << ", " << pValue[2].y << ", " << pValue[2].z << ", " << pValue[2].w << "}, "
				<< "{" << pValue[3].x << ", " << pValue[3].y << ", " << pValue[3].z << ", " << pValue[3].w << "}}";
			return stringStream.str();
		}
#pragma endregion
	};


	TEST_CLASS(DatumTest)
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

		TEST_METHOD(Datum_Constructor_Default)
		{
			DatumTestFunctions<int32_t>::TestDefaultConstructor();
			DatumTestFunctions<float>::TestDefaultConstructor();
			DatumTestFunctions<std::string>::TestDefaultConstructor();
			DatumTestFunctions<glm::vec4>::TestDefaultConstructor();
			DatumTestFunctions<glm::mat4x4>::TestDefaultConstructor();
		}

		TEST_METHOD(Datum_SetType)
		{
			DatumTestFunctions<int32_t>::TestSetType(DatumType::INTEGER, DatumType::FLOAT);
			DatumTestFunctions<float>::TestSetType(DatumType::FLOAT, DatumType::STRING);
			DatumTestFunctions<std::string>::TestSetType(DatumType::STRING, DatumType::VECTOR_4);
			DatumTestFunctions<glm::vec4>::TestSetType(DatumType::VECTOR_4, DatumType::MATRIX_4x4);
			DatumTestFunctions<glm::mat4x4>::TestSetType(DatumType::MATRIX_4x4, DatumType::INTEGER);
		}

		TEST_METHOD(Datum_SetSize)
		{
			DatumTestFunctions<int32_t>::TestSetSize(DatumType::INTEGER);
			DatumTestFunctions<float>::TestSetSize(DatumType::INTEGER);
			DatumTestFunctions<std::string>::TestSetSize(DatumType::INTEGER);
			DatumTestFunctions<glm::vec4>::TestSetSize(DatumType::INTEGER);
			DatumTestFunctions<glm::mat4x4>::TestSetSize(DatumType::INTEGER);
		}

		TEST_METHOD(Datum_PushBack)
		{
			DatumTestFunctions<int32_t, float>::TestPushBack(DatumType::INTEGER, 10, 20, 30, 30.0f);
			DatumTestFunctions<float, std::string>::TestPushBack(DatumType::FLOAT, 10.f, 20.f, 30.f, "");
			DatumTestFunctions<std::string, glm::vec4>::TestPushBack(DatumType::STRING, "Alpha", "Charlie", "Delta", glm::vec4());
			DatumTestFunctions<glm::vec4, glm::mat4x4>::TestPushBack(DatumType::VECTOR_4, glm::vec4(), glm::vec4(), glm::vec4(), glm::mat4x4());
			DatumTestFunctions<glm::mat4x4, int32_t>::TestPushBack(DatumType::MATRIX_4x4, glm::mat4x4(), glm::mat4x4(), glm::mat4x4(), 10);
		}

		TEST_METHOD(Datum_PopBack)
		{
			DatumTestFunctions<int32_t>::TestPopBack(10, 20);
			DatumTestFunctions<float>::TestPopBack(10.f, 20.f);
			DatumTestFunctions<std::string>::TestPopBack("Alpha", "Delta");
			DatumTestFunctions<glm::vec4>::TestPopBack(glm::vec4(), glm::vec4());
			DatumTestFunctions<glm::mat4x4>::TestPopBack(glm::mat4x4(), glm::mat4x4());
		}

		TEST_METHOD(Datum_Clear)
		{
			DatumTestFunctions<int32_t>::TestClear(10, 20);
			DatumTestFunctions<float>::TestClear(10.f, 20.f);
			DatumTestFunctions<std::string>::TestClear("Alpha", "Delta");
			DatumTestFunctions<glm::vec4>::TestClear(glm::vec4(), glm::vec4());
			DatumTestFunctions<glm::mat4x4>::TestClear(glm::mat4x4(), glm::mat4x4());
		}

		TEST_METHOD(Datum_SetStorage)
		{
			const uint32_t arrSize = 3;
			int32_t intArr[arrSize] = {10, 20, 30};
			float floatArr[arrSize] = { 10.f, 20.f, 30.f };
			std::string strArr[arrSize] = {"Alpha", "Charlie", "Delta"};
			glm::vec4 vecArr[arrSize] = {glm::vec4(), glm::vec4(), glm::vec4()};
			glm::mat4x4 matArr[arrSize] = {glm::mat4x4(), glm::mat4x4(), glm::mat4x4()};

			DatumTestFunctions<int32_t, float>::TestSetStorage(DatumType::INTEGER, &intArr[0], arrSize, &floatArr[0], arrSize);
			DatumTestFunctions<float, std::string>::TestSetStorage(DatumType::FLOAT, &floatArr[0], arrSize, &strArr[0], arrSize);
			DatumTestFunctions<std::string, glm::vec4>::TestSetStorage(DatumType::STRING, &strArr[0], arrSize, &vecArr[0], arrSize);
			DatumTestFunctions<glm::vec4, glm::mat4x4>::TestSetStorage(DatumType::VECTOR_4, &vecArr[0], arrSize, &matArr[0], arrSize);
			DatumTestFunctions<glm::mat4x4, int32_t>::TestSetStorage(DatumType::MATRIX_4x4, &matArr[0], arrSize, &intArr[0], arrSize);
		}

		TEST_METHOD(Datum_ComparisonOperator)
		{
			DatumTestFunctions<int32_t>::TestComparisonOperator(10, 20, 30);
			DatumTestFunctions<float>::TestComparisonOperator(10.f, 20.f, 30.f);
			DatumTestFunctions<std::string>::TestComparisonOperator("Alpha", "Charlie", "Delta");

			glm::vec4 vec1(10, 20, 30, 40);
			glm::vec4 vec2(50, 60, 70, 80);
			glm::vec4 vec3(90, 80, 70, 460);
			DatumTestFunctions<glm::vec4>::TestComparisonOperator(vec1, vec2, vec3);

			glm::mat4x4 mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			glm::mat4x4 mat2(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
			glm::mat4x4 mat3(100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600);
			DatumTestFunctions<glm::mat4x4>::TestComparisonOperator(mat1, mat2, mat3);
		}

		TEST_METHOD(Datum_AssignmentOperator)
		{
			const uint32_t arrSize = 3;
			int32_t intArr[arrSize] = { 10, 20, 30 };
			float floatArr[arrSize] = { 10.f, 20.f, 30.f };
			std::string strArr[arrSize] = { "Alpha", "Charlie", "Delta" };
			glm::vec4 vecArr[arrSize] = { glm::vec4(), glm::vec4(), glm::vec4() };
			glm::mat4x4 matArr[arrSize] = { glm::mat4x4(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700), glm::mat4x4(), glm::mat4x4() };

			DatumTestFunctions<int32_t>::TestAssignmentOperator(DatumType::INTEGER, 10, 20, 30, &intArr[0], arrSize);
			DatumTestFunctions<float>::TestAssignmentOperator(DatumType::FLOAT, 10.f, 20.f, 30.f, &floatArr[0], arrSize);
			DatumTestFunctions<std::string>::TestAssignmentOperator(DatumType::STRING, "Gamma", "Beta", "Bar", &strArr[0], arrSize);
			DatumTestFunctions<glm::vec4>::TestAssignmentOperator(DatumType::VECTOR_4, glm::vec4(1,2,3,4), glm::vec4(5,6,7,8), glm::vec4(9, 0, 1, 2), &vecArr[0], arrSize);
			DatumTestFunctions<glm::mat4x4>::TestAssignmentOperator(DatumType::MATRIX_4x4, glm::mat4x4(1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6), glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 7), glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 8), &matArr[0], arrSize);
		}

		TEST_METHOD(Datum_CopyConstuctor)
		{
			const uint32_t arrSize = 3;
			int32_t intArr[arrSize] = { 10, 20, 30 };
			float floatArr[arrSize] = { 10.f, 20.f, 30.f };
			std::string strArr[arrSize] = { "Alpha", "Charlie", "Delta" };
			glm::vec4 vecArr[arrSize] = { glm::vec4(), glm::vec4(), glm::vec4() };
			glm::mat4x4 matArr[arrSize] = { glm::mat4x4(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700), glm::mat4x4(), glm::mat4x4() };

			DatumTestFunctions<int32_t>::TestCopyConstructor(DatumType::INTEGER, 10, 20, 30, &intArr[0], arrSize);
			DatumTestFunctions<float>::TestCopyConstructor(DatumType::FLOAT, 10.f, 20.f, 30.f, &floatArr[0], arrSize);
			DatumTestFunctions<std::string>::TestCopyConstructor(DatumType::STRING, "Gamma", "Beta", "Bar", &strArr[0], arrSize);
			DatumTestFunctions<glm::vec4>::TestCopyConstructor(DatumType::VECTOR_4, glm::vec4(1, 2, 3, 4), glm::vec4(5, 6, 7, 8), glm::vec4(9, 0, 1, 2), &vecArr[0], arrSize);
			DatumTestFunctions<glm::mat4x4>::TestCopyConstructor(DatumType::MATRIX_4x4, glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6), glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 7), glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 8), &matArr[0], arrSize);
		}

		TEST_METHOD(Datum_Get)
		{
			DatumTestFunctions<int32_t>::TestGet(3U, 10, 20, 30);
			DatumTestFunctions<float>::TestGet(3U, 10.f, 20.f, 30.f);
			DatumTestFunctions<std::string>::TestGet(3U, "Gamma", "Beta", "Bar");
			DatumTestFunctions<glm::vec4>::TestGet(3U, glm::vec4(1, 2, 3, 4), glm::vec4(5, 6, 7, 8), glm::vec4(9, 0, 1, 2));
			DatumTestFunctions<glm::mat4x4>::TestGet(3U, glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6), glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 7), glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 8));
		}

		TEST_METHOD(Datum_Set)
		{
			DatumTestFunctions<int32_t, float>::TestSet(10, 20, 30, 10.f);
			DatumTestFunctions<float, std::string>::TestSet(10.f, 20.f, 30.f, "Alpha");
			DatumTestFunctions<std::string, glm::vec4>::TestSet("Alpha", "Beta", "Delta", glm::vec4());
			DatumTestFunctions<glm::vec4, std::string>::TestSet(glm::vec4(1,2,3,4), glm::vec4(1, 3, 2, 4), glm::vec4(1, 4, 6, 4), "Delta");
			DatumTestFunctions<glm::mat4x4, float>::TestSet(glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6), glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 1, 5, 7), glm::mat4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 5, 3, 4, 5, 8), 10.f);
		}

		TEST_METHOD(Datum_ToString)
		{
			DatumTestFunctions<int32_t>::TestToString(10);
			DatumTestFunctions<float>::TestToString(10.f);
			DatumTestFunctions<std::string>::TestToString("Alpha");
			DatumTestFunctions<glm::vec4>::TestToString(glm::vec4(10.f, 30.f, 40.234f, 50.f));
			DatumTestFunctions<glm::mat4x4>::TestToString(glm::mat4x4(1.f,2,3,4,5,6.789f,7,8,9,0.98f,1,2,3,4,5,6));
		}

		TEST_METHOD(Datum_SetFromString)
		{
			DatumTestFunctions<int32_t>::TestSetFromString(DatumType::INTEGER, 10, "10", 20, "20");

			float f1 = 10.34f;
			float f2 = 43.66f;
			DatumTestFunctions<float>::TestSetFromString(DatumType::FLOAT, f1, DatumTestFunctions<float>::ToString(f1), f2, DatumTestFunctions<float>::ToString(f2));

			DatumTestFunctions<std::string>::TestSetFromString(DatumType::STRING, "Alpha", "Alpha", "Beta", "Beta");

			glm::vec4 vec1(1.77f, 6.88f, 9.7f, 877.8f);
			glm::vec4 vec2(9.7f, 0.88f, 9.78f, 87.8f);
			DatumTestFunctions<glm::vec4>::TestSetFromString(DatumType::VECTOR_4, vec1, DatumTestFunctions<glm::vec4>::ToString(vec1), vec2, DatumTestFunctions<glm::vec4>::ToString(vec2));
			
			glm::mat4x4 mat1(1, 2, 3, 4, 5, 6, 7.45f, 8, 9, 0.844f, 1, 2, 3.834f, 4, 5, 6);
			glm::mat4x4 mat2(1, 2, 3, 4, 5.543f, 6, 7.45f, 8, 9, 0.844f, 1, 2.786f, 3.834f, 4, 5, 6);
			DatumTestFunctions<glm::mat4x4>::TestSetFromString(DatumType::MATRIX_4x4, mat1, DatumTestFunctions<glm::mat4x4>::ToString(mat1), mat2, DatumTestFunctions<glm::mat4x4>::ToString(mat2));
		}

		TEST_METHOD(MoveSemantics)
		{
			int a = 10;
			Datum d;
			d.PushBack(a);

			Datum d2 = std::move(d);
			Assert::AreEqual(a, d2.Get<int>());
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState DatumTest::sStartMemState;
}