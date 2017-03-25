#pragma once
#include "IXmlParseHelper.h"

namespace NoobEngine
{
	namespace Parsers
	{
		class XmlParseHelperConstruction : public IXmlParseHelper
		{
		public:
			/**
				@brief Default constructor
			*/
			XmlParseHelperConstruction();

			/**
				@brief Default destructor
			*/
			~XmlParseHelperConstruction();

			/**
				@brief Initialize this helper. This will get called just before each file is parsed.
				@param[in] pXmlParseMaster The XmlParseMaster that this helper is attached to.
				@exception std::exception Throws exception if the SharedData that the XmlParseMaster has SharedData that is not of type XmlTableParser.
			*/
			virtual void Initialize(XmlParseMaster* pXmlParseMaster) override;

			/**
				@brief Called everytime a start element tag is hit in the XML.
				@param[in] pElement String that holds the element
				@param[in] pAttributes Hashmap that holds all the attributes.
			*/
			virtual bool StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes) override;

			/**
				@brief Called everytime a end of the element is reached in the XML.
				@param[in] pElement String that holds the element.
			*/
			virtual bool EndElementHandler(const std::string& pElement) override;
		};
	}
}