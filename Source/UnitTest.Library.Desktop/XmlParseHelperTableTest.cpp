#include "pch.h"
#include "CppUnitTest.h"
#include "Parsers/XmlParseMaster.h"
#include "Parsers/XmlParseHelperTable.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(XmlParseHelperTable)
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
				//Assert::Fail(L"Memory Leaks!");
			}
		}

		TEST_METHOD(StringTest)
		{
			const char* xmlGrammar = "Resources/TableXmlGrammar.xml";

			// things needed for parser
			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser sharedData;
			NoobEngine::Parsers::XmlParseHelperTable helper;

			// parser
			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			parser.ParseFromFile(xmlGrammar);

			Assert::AreEqual(std::string("Plato"), sharedData.GetRootNode()["Name"].Get<std::string>());

			Assert::AreEqual(std::string("Plato"), sharedData.GetRootNode()["ArrayString"].Get<std::string>(0));
			Assert::AreEqual(std::string("NPC1"), sharedData.GetRootNode()["ArrayString"].Get<std::string>(1));
			Assert::AreEqual(std::string("NPC2"), sharedData.GetRootNode()["ArrayString"].Get<std::string>(2));

			delete &sharedData.GetRootNode();
		}

		TEST_METHOD(IntTest)
		{
			const char* xmlGrammar = "Resources/TableXmlGrammar.xml";

			// things needed for parser
			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser sharedData;
			NoobEngine::Parsers::XmlParseHelperTable helper;

			// parser
			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			parser.ParseFromFile(xmlGrammar);

			Assert::AreEqual(3, sharedData.GetRootNode()["Life"].Get<int>());

			Assert::AreEqual(1, sharedData.GetRootNode()["ArrayInt"].Get<int>(0));
			Assert::AreEqual(2, sharedData.GetRootNode()["ArrayInt"].Get<int>(1));
			Assert::AreEqual(3, sharedData.GetRootNode()["ArrayInt"].Get<int>(2));

			delete &sharedData.GetRootNode();
		}

		TEST_METHOD(FloatTest)
		{
			const char* xmlGrammar = "Resources/TableXmlGrammar.xml";

			// things needed for parser
			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser sharedData;
			NoobEngine::Parsers::XmlParseHelperTable helper;

			// parser
			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			parser.ParseFromFile(xmlGrammar);

			Assert::AreEqual(100.0f, sharedData.GetRootNode()["Health"].Get<float>());

			Assert::AreEqual(1.0f, sharedData.GetRootNode()["ArrayFloat"].Get<float>(0));
			Assert::AreEqual(2.0f, sharedData.GetRootNode()["ArrayFloat"].Get<float>(1));
			Assert::AreEqual(3.0f, sharedData.GetRootNode()["ArrayFloat"].Get<float>(2));

			delete &sharedData.GetRootNode();
		}

		TEST_METHOD(Vec4Test)
		{
			const char* xmlGrammar = "Resources/TableXmlGrammar.xml";

			// things needed for parser
			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser sharedData;
			NoobEngine::Parsers::XmlParseHelperTable helper;

			// parser
			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			parser.ParseFromFile(xmlGrammar);

			Assert::IsTrue(glm::vec4(0, 0, 0, 0) == sharedData.GetRootNode()["Pos"].Get<glm::vec4>());

			Assert::IsTrue(glm::vec4(0, 0, 0, 0) == sharedData.GetRootNode()["ArrayVec4"].Get<glm::vec4>(0));
			Assert::IsTrue(glm::vec4(1, 2, 3, 4) == sharedData.GetRootNode()["ArrayVec4"].Get<glm::vec4>(1));
			Assert::IsTrue(glm::vec4(5, 6, 7, 8) == sharedData.GetRootNode()["ArrayVec4"].Get<glm::vec4>(2));

			delete &sharedData.GetRootNode();
		}

		TEST_METHOD(Mat4x4Test)
		{
			const char* xmlGrammar = "Resources/TableXmlGrammar.xml";

			// things needed for parser
			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser sharedData;
			NoobEngine::Parsers::XmlParseHelperTable helper;

			// parser
			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			parser.ParseFromFile(xmlGrammar);

			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) == sharedData.GetRootNode()["Transform"].Get<glm::mat4x4>());

			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) == sharedData.GetRootNode()["ArrayMat4x4"].Get<glm::mat4x4>(0));
			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0) == sharedData.GetRootNode()["ArrayMat4x4"].Get<glm::mat4x4>(1));
			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 0) == sharedData.GetRootNode()["ArrayMat4x4"].Get<glm::mat4x4>(2));

			delete &sharedData.GetRootNode();
		}

		TEST_METHOD(TableTest)
		{
			const char* xmlGrammar = "Resources/TableXmlGrammar.xml";

			// things needed for parser
			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser sharedData;
			NoobEngine::Parsers::XmlParseHelperTable helper;

			// parser
			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			parser.ParseFromFile(xmlGrammar);

			NoobEngine::Runtime::Scope& playerScope = *sharedData.GetRootNode()["Player"].Get<NoobEngine::Runtime::Scope*>();

			Assert::AreEqual(std::string("Plato"), playerScope["Name"].Get<std::string>());
			Assert::AreEqual(3, playerScope["LifeCount"].Get<int>());
			Assert::AreEqual(200.0f, playerScope["Health"].Get<float>());

			delete &sharedData.GetRootNode();
		}

		TEST_METHOD(RTTIMethods)
		{
			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser sharedData;

			Assert::IsTrue(sharedData.Is(NoobEngine::Parsers::XmlParseMaster::SharedData::TypeIdClass()));
			Assert::IsTrue(sharedData.Is(NoobEngine::Parsers::XmlParseMaster::SharedData::TypeName()));

			NoobEngine::Parsers::XmlParseMaster::SharedData* sharedDataPtr = sharedData.As<NoobEngine::Parsers::XmlParseMaster::SharedData>();

			Assert::IsTrue(sharedDataPtr != nullptr);
		}

		TEST_METHOD(CloneTest)
		{
			const char* xmlGrammar = "Resources/TableXmlGrammar.xml";

			// things needed for parser
			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser sharedData2;
			NoobEngine::Parsers::XmlParseHelperTable helper;

			// parser
			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(sharedData2);
			parser.AddHelper(helper);

			parser.ParseFromFile(xmlGrammar);

			NoobEngine::Parsers::XmlParseMaster* cloneParser = parser.Clone();
			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser& sharedData = *(cloneParser->GetSharedData()->As<NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser>());

			// string
			Assert::AreEqual(std::string("Plato"), sharedData2.GetRootNode()["Name"].Get<std::string>());

			Assert::AreEqual(std::string("Plato"), sharedData.GetRootNode()["ArrayString"].Get<std::string>(0));
			Assert::AreEqual(std::string("NPC1"), sharedData.GetRootNode()["ArrayString"].Get<std::string>(1));
			Assert::AreEqual(std::string("NPC2"), sharedData.GetRootNode()["ArrayString"].Get<std::string>(2));
			
			// int
			Assert::AreEqual(3, sharedData.GetRootNode()["Life"].Get<int>());

			Assert::AreEqual(1, sharedData.GetRootNode()["ArrayInt"].Get<int>(0));
			Assert::AreEqual(2, sharedData.GetRootNode()["ArrayInt"].Get<int>(1));
			Assert::AreEqual(3, sharedData.GetRootNode()["ArrayInt"].Get<int>(2));

			// float
			Assert::AreEqual(100.0f, sharedData.GetRootNode()["Health"].Get<float>());

			Assert::AreEqual(1.0f, sharedData.GetRootNode()["ArrayFloat"].Get<float>(0));
			Assert::AreEqual(2.0f, sharedData.GetRootNode()["ArrayFloat"].Get<float>(1));
			Assert::AreEqual(3.0f, sharedData.GetRootNode()["ArrayFloat"].Get<float>(2));

			// vec4
			Assert::IsTrue(glm::vec4(0, 0, 0, 0) == sharedData.GetRootNode()["Pos"].Get<glm::vec4>());

			Assert::IsTrue(glm::vec4(0, 0, 0, 0) == sharedData.GetRootNode()["ArrayVec4"].Get<glm::vec4>(0));
			Assert::IsTrue(glm::vec4(1, 2, 3, 4) == sharedData.GetRootNode()["ArrayVec4"].Get<glm::vec4>(1));
			Assert::IsTrue(glm::vec4(5, 6, 7, 8) == sharedData.GetRootNode()["ArrayVec4"].Get<glm::vec4>(2));

			//mat4x4
			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) == sharedData.GetRootNode()["Transform"].Get<glm::mat4x4>());

			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) == sharedData.GetRootNode()["ArrayMat4x4"].Get<glm::mat4x4>(0));
			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0) == sharedData.GetRootNode()["ArrayMat4x4"].Get<glm::mat4x4>(1));
			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 0) == sharedData.GetRootNode()["ArrayMat4x4"].Get<glm::mat4x4>(2));

			// table
			NoobEngine::Runtime::Scope& playerScope = *sharedData.GetRootNode()["Player"].Get<NoobEngine::Runtime::Scope*>();

			Assert::AreEqual(std::string("Plato"), playerScope["Name"].Get<std::string>());
			Assert::AreEqual(3, playerScope["LifeCount"].Get<int>());
			Assert::AreEqual(200.0f, playerScope["Health"].Get<float>());

			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser* ptr1 = cloneParser->GetSharedData()->As<NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser>();
			NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser* ptr2 = parser.GetSharedData()->As<NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser>();
			ptr1;
			ptr2;
			
			delete &(parser.GetSharedData()->As<NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser>()->GetRootNode());
			delete &(cloneParser->GetSharedData()->As<NoobEngine::Parsers::XmlParseHelperTable::XmlTableParser>()->GetRootNode());
			delete cloneParser;
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlParseHelperTable::sStartMemState;
}