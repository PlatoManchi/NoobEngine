#pragma once
#include "Parsers/IXmlParseHelper.h"

namespace SupportingClasses
{
	class TestXmlParseHelper : public NoobEngine::Parsers::IXmlParseHelper
	{
	public:
		int mStartElementCount;
		int mEndElementCount;

		/**
			Default constructor
		*/
		TestXmlParseHelper();

		/**
			Default destructor
		*/
		~TestXmlParseHelper() = default;

		/**
			Overridden Initialize function from IXmlParseHelper
		*/
		virtual void Initialize(NoobEngine::Parsers::XmlParseMaster* pXmlParseMaster) override;

		/**
			Overridden StartElementHandler function from IXmlParseHelper to handle the starting of the start of element
		*/
		virtual bool StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes) override;

		/**
			Overridden EndElementHandler function from IXmlParseHelper to handle the starting of the end of element
		*/
		virtual bool EndElementHandler(const std::string& pElement) override;

		/**
			Overridden CharDataHandler function from IXmlParseHelper to handle the Characters between the elements
		*/
		virtual bool CharDataHandler(const std::string& pCharData) override;

		/**
			Overridden Clone function from IXmlParseHelper to handle the cloning of the helper
		*/
		virtual IXmlParseHelper* Clone() const override;
	};
}