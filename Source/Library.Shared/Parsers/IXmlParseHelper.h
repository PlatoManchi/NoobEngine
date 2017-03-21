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
				Initialize this helper. This will get called just before each file is parsed.
			*/
			virtual void Initialize(XmlParseMaster* pXmlParseMaster);

			virtual bool StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes) = 0;
			virtual bool EndElementHandler(const std::string& pElement) = 0;
			virtual bool CharDataHandler(const std::string& pCharData) = 0;
			virtual IXmlParseHelper* Clone() const = 0;

		protected:
			XmlParseMaster* mXmlParseMaster;
		};
	}
}