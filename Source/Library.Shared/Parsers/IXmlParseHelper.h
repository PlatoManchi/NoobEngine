#pragma once
#include "Container/Hashmap.h"
#include "Parsers/XmlParseMaster.h"

namespace NoobEngine
{
	namespace Parsers
	{
		// forward declaration
		class XmlParseMaster;

		class IXmlParseHelper
		{
		public:
			IXmlParseHelper();
			virtual ~IXmlParseHelper();

			/**
				@brief Initialize this helper. This will get called just before each file is parsed.
				@param[in] pXmlParseMaster The XmlParseMaster that this helper is attached to.
			*/
			virtual void Initialize(XmlParseMaster* pXmlParseMaster);

			/**
				@brief Called everytime a start element tag is hit in the XML.
				@param[in] pElement String that holds the element
				@param[in] pAttributes Hashmap that holds all the attributes.
			*/
			virtual bool StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes) = 0;

			/**
				@brief Called everytime a end of the element is reached in the XML.
				@param[in] pElement String that holds the element.
			*/
			virtual bool EndElementHandler(const std::string& pElement) = 0;

			/**
				@brief Called while parsing any element with char data is hit.
				@details Note that even the white spaces between elements are considered as characters.
				@param[in] pCharData The data that is there between tags.
			*/
			virtual bool CharDataHandler(const std::string& pCharData);

			/**
				@brief Create a clone of XmlParseHelper and return the pointer to the clone.
				@return IXmlParseHelper pointer that points to the new cloned parse helper.
			*/
			virtual IXmlParseHelper* Clone() const = 0;

		protected:
			/**
				Holds the pointer to XmlParseMaster.
			*/
			XmlParseMaster* mXmlParseMaster;
		};
	}
}