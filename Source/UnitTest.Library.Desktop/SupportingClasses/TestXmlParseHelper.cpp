#include "pch.h"
#include "TestXmlParseHelper.h"
#include <windows.h>
#include "Parsers/XmlParseMaster.h"

namespace SupportingClasses
{
	TestXmlParseHelper::TestXmlParseHelper() : 
		mStartElementCount(0), mEndElementCount(0)
	{

	}

	void TestXmlParseHelper::Initialize(NoobEngine::Parsers::XmlParseMaster* pXmlParseMaster)
	{
		IXmlParseHelper::Initialize(pXmlParseMaster);

		mStartElementCount = 0;
		mEndElementCount = 0;
	}

	bool TestXmlParseHelper::StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes)
	{
		std::string debugStr = "";
		mStartElementCount++;
		
		if (mXmlParseMaster->GetSharedData())
		{
			for (uint32_t i = 0; i < mXmlParseMaster->GetSharedData()->Depth() - 1; i++)
			{
				debugStr += "\t";
			}
		}

		debugStr += "<" + pElement + " ";
		
		for (std::pair<std::string, std::string>& pair : pAttributes)
		{
			debugStr += pair.first + " = \"" + pair.second + "\" ";
		}
		debugStr.pop_back();
		debugStr += ">\n";

		OutputDebugString(debugStr.c_str());
		
		return true;
	}

	bool TestXmlParseHelper::EndElementHandler(const std::string& pElement)
	{
		std::string debugStr = "";
		mEndElementCount++;

		if (mXmlParseMaster->GetSharedData())
		{
			for (uint32_t i = 0; i < mXmlParseMaster->GetSharedData()->Depth() - 1; i++)
			{
				debugStr += "\t";
			}
		}

		debugStr += "</" + pElement + ">\n";
		OutputDebugString(debugStr.c_str());
		return true;
	}

	bool TestXmlParseHelper::CharDataHandler(const std::string& pCharData)
	{
		pCharData;
		return true;
	}

	NoobEngine::Parsers::IXmlParseHelper* TestXmlParseHelper::Clone() const
	{
		TestXmlParseHelper* cloneHelper = new TestXmlParseHelper();
		
		return cloneHelper;
	}
}