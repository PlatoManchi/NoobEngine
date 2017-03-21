#include "pch.h"
#include "CppUnitTest.h"
#include "Parsers/XmlParseMaster.h"
#include "SupportingClasses/TestXmlParseHelper.h"

#include <windows.h>
#include <string>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(XmlParseMasterTest)
	{
	public:
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

		TEST_METHOD(ParseInvalidXML)
		{
			const char* xmlInvalid = "<Class>"
				"<Student name = \"Alpha\" id = \"1\">"
				"<Sem1 grade = \"A\" / >"// adding space after / to make the xml invalid
				"<Sem1 grade = \"B\" />"
				"<Sem1 grade = \"TBD\" />"
				"</Student>"
				"<Student name = \"Beta\" id = \"2\">"
				"<Sem1 grade = \"A+\" />"
				"<Sem1 grade = \"A\" />"
				"<Sem1 grade = \"TBD\" />"
				"</Student>"
				"</Class>";

			NoobEngine::Parsers::XmlParseMaster parser;
			SupportingClasses::TestXmlParseHelper helper;

			NoobEngine::Parsers::XmlParseMaster::SharedData sharedData;

			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			Assert::ExpectException<std::exception>([&] {parser.Parse(nullptr); });

			// parsing invalid xml
			parser.Parse(xmlInvalid);

			Assert::AreNotEqual(helper.mStartElementCount, helper.mEndElementCount);

			
		}

		TEST_METHOD(ParseValidXML)
		{
			const char* xmlValid = "<Class>"
				"<Student name = \"Alpha\" id = \"1\">"
				"<Sem1 grade = \"A\" />"
				"<Sem1 grade = \"B\" />"
				"<Sem1 grade = \"TBD\" />"
				"</Student>"
				"<Student name = \"Beta\" id = \"2\">"
				"<Sem1 grade = \"A+\" />"
				"<Sem1 grade = \"A\" />"
				"<Sem1 grade = \"TBD\" />"
				"</Student>"
				"</Class>";

			NoobEngine::Parsers::XmlParseMaster parser;
			SupportingClasses::TestXmlParseHelper helper;

			NoobEngine::Parsers::XmlParseMaster::SharedData sharedData;

			Assert::AreEqual(0U, sharedData.Depth());

			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			// parsing valid xml
			parser.Parse(xmlValid);
			Assert::AreEqual(helper.mStartElementCount, helper.mEndElementCount);
			Assert::AreEqual(9, helper.mStartElementCount);
			Assert::AreEqual(9, helper.mEndElementCount);

			Assert::AreEqual(0U, sharedData.Depth());
		}

		TEST_METHOD(ParseFromFile) 
		{
			const char* validXMLFilePath = "Resources/SampleXml.xml";
			const char* invalidXMLFilePath = "InvalidFilePath.xml";

			std::ifstream xmlFileStream("Resources/SampleXml.xml");
			if (xmlFileStream)
			{
				std::stringstream buffer;
				buffer << xmlFileStream.rdbuf();
				string xmlStr = buffer.str();
			}

			NoobEngine::Parsers::XmlParseMaster parser;
			SupportingClasses::TestXmlParseHelper helper;

			NoobEngine::Parsers::XmlParseMaster::SharedData sharedData;

			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			Assert::ExpectException<std::exception>([&] { parser.ParseFromFile(nullptr); });
			Assert::ExpectException<std::exception>([&] { parser.ParseFromFile(invalidXMLFilePath); });

			parser.ParseFromFile(validXMLFilePath);
			Assert::AreEqual(helper.mStartElementCount, helper.mEndElementCount);
		}

		TEST_METHOD(SharedDataClone)
		{
			NoobEngine::Parsers::XmlParseMaster::SharedData sharedData;
			NoobEngine::Parsers::XmlParseMaster parser;
			
			const char* validXMLFilePath = "Resources/SampleXml.xml";

			parser.ParseFromFile(validXMLFilePath);

			Assert::AreEqual(0U, sharedData.Depth());

			NoobEngine::Parsers::XmlParseMaster::SharedData* cloneSharedData = sharedData.Clone();

			Assert::AreEqual(0U, cloneSharedData->Depth());

			delete cloneSharedData;
		}

		TEST_METHOD(GetFileName)
		{
			const char* validXMLFilePath = "Resources/SampleXml.xml";

			NoobEngine::Parsers::XmlParseMaster parser;
			SupportingClasses::TestXmlParseHelper helper;

			NoobEngine::Parsers::XmlParseMaster::SharedData sharedData;

			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			parser.ParseFromFile(validXMLFilePath);

			Assert::AreEqual(std::string(validXMLFilePath), parser.GetFileName());
		}

		TEST_METHOD(MasterClone)
		{
			const char* validXMLFilePath = "Resources/SampleXml.xml";

			NoobEngine::Parsers::XmlParseMaster parser;
			SupportingClasses::TestXmlParseHelper helper;

			NoobEngine::Parsers::XmlParseMaster::SharedData sharedData;

			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			Assert::AreEqual(0U, sharedData.Depth());
			Assert::AreEqual(helper.mStartElementCount, helper.mEndElementCount);
			Assert::AreEqual(0, helper.mStartElementCount);
			Assert::AreEqual(0, helper.mEndElementCount);

			parser.ParseFromFile(validXMLFilePath);

			Assert::AreEqual(helper.mStartElementCount, helper.mEndElementCount);
			Assert::AreNotEqual(0, helper.mStartElementCount);
			Assert::AreNotEqual(0, helper.mEndElementCount);

			Assert::AreEqual(0U, sharedData.Depth());

			NoobEngine::Parsers::XmlParseMaster* cloneMaster = parser.Clone();

			Assert::AreEqual(0U, cloneMaster->GetSharedData()->Depth());
			Assert::AreEqual(std::string(""), cloneMaster->GetFileName());

			Assert::ExpectException<std::exception>([&] { cloneMaster->AddHelper(helper); });
			Assert::ExpectException<std::exception>([&] { cloneMaster->RemoveHelper(helper); });

			delete cloneMaster;
		}

		TEST_METHOD(RemoveHelper)
		{
			const char* validXMLFilePath = "Resources/SampleXml.xml";

			NoobEngine::Parsers::XmlParseMaster parser;
			SupportingClasses::TestXmlParseHelper helper;

			NoobEngine::Parsers::XmlParseMaster::SharedData sharedData;

			parser.SetSharedData(sharedData);
			parser.AddHelper(helper);

			NoobEngine::Parsers::XmlParseMaster* cloneMaster = parser.Clone();

			parser.RemoveHelper(helper);

			parser.ParseFromFile(validXMLFilePath);

			Assert::AreEqual(helper.mStartElementCount, helper.mEndElementCount);
			Assert::AreEqual(0, helper.mStartElementCount);
			Assert::AreEqual(0, helper.mEndElementCount);

			Assert::ExpectException<std::exception>([&] { cloneMaster->AddHelper(helper); });
			Assert::ExpectException<std::exception>([&] { cloneMaster->RemoveHelper(helper); });

			delete cloneMaster;
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XmlParseMasterTest::sStartMemState;
}