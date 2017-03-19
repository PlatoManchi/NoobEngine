#pragma once
#include "expat_external.h"

namespace NoobEngine
{
	namespace Parsers
	{
		class IXmlParseHelper
		{
		public:
			virtual void Initialize();
			virtual bool StartElementHandler(void* pData, const XML_Char* pElement, const XML_Char** pAttributes);
			virtual bool EndElementHandler(void* pData, const XML_Char* pElement);
			virtual bool CharDataHandler(void* pData, const XML_Char* pElement, int pLength);
			virtual void Clone() = 0;
		private:

		};
	}
}