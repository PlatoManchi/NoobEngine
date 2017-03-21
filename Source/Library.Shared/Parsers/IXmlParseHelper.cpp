#include "pch.h"
#include "IXmlParseHelper.h"

namespace NoobEngine
{
	namespace Parsers
	{
		IXmlParseHelper::IXmlParseHelper() : 
			mXmlParseMaster(nullptr)
		{ }

		IXmlParseHelper::~IXmlParseHelper()
		{ }

		void IXmlParseHelper::Initialize(XmlParseMaster* pXmlParseMaster)
		{
			mXmlParseMaster = pXmlParseMaster;
		}
	}
}