#pragma once
#include "IXmlParseHelper.h"

namespace NoobEngine
{
	namespace Parsers
	{
		class WorldParseHelper : public IXmlParseHelper
		{
		public:
			/**
				@brief Default constructor
			*/
			WorldParseHelper();

			/**
				@brief Default destructor
			*/
			virtual ~WorldParseHelper();

			/**
				@brief Initialize this helper. This will get called just before each file is parsed.
				@param[in] pXmlParseMaster The XmlParseMaster that this helper is attached to.
			*/
			virtual void Initialize(XmlParseMaster* pXmlParseMaster);

			/**
				@brief Called every time a start element tag is hit in the XML.
				@param[in] pElement String that holds the element
				@param[in] pAttributes Hashmap that holds all the attributes.
			*/
			virtual bool StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes) = 0;

			/**
				@brief Called every time a end of the element is reached in the XML.
				@param[in] pElement String that holds the element.
			*/
			virtual bool EndElementHandler(const std::string& pElement) = 0;

			/**
				@brief Create a clone of XmlParseHelper and return the pointer to the clone.
				@return IXmlParseHelper pointer that points to the new cloned parse helper.
			*/
			virtual IXmlParseHelper* Clone() const = 0;
		};
	}
}