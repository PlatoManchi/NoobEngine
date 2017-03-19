#include "pch.h"
#include "XmlParseMaster.h"

namespace NoobEngine
{
	namespace Parsers
	{
		
#pragma region SharedData
		RTTI_DEFINITIONS(XmlParseMaster::SharedData)

		XmlParseMaster::SharedData::SharedData()
		{

		}

		XmlParseMaster::SharedData* XmlParseMaster::SharedData::Clone() const
		{
			return nullptr;
		}

		void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster* const pXmlParseMaster)
		{
			mXmlParseMaster = pXmlParseMaster;
		}

		XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster() const
		{
			return mXmlParseMaster;
		}
		void XmlParseMaster::SharedData::IncrementDepth()
		{
			++mDepth;
		}

		void XmlParseMaster::SharedData::DecrementDepth()
		{
			--mDepth;
		}

		uint32_t XmlParseMaster::SharedData::Depth() const
		{
			return mDepth;
		}
#pragma endregion
#pragma region XmlParseMaster
		XmlParseMaster::XmlParseMaster() : 
			mParser(XML_ParserCreate(NULL)), mFilePath(nullptr), mSharedData(nullptr)
		{
			XML_SetUserData(mParser, this);
			XML_SetElementHandler(mParser, &XmlParseMaster::StartElementHandler, &XmlParseMaster::EndElementHandler);
			XML_SetCharacterDataHandler(mParser, &XmlParseMaster::CharDataHandler);
		}

		XmlParseMaster::~XmlParseMaster()
		{
			XML_ParserFree(mParser);
		}

		XmlParseMaster* XmlParseMaster::Clone()
		{
			return nullptr;
		}

		void XmlParseMaster::AddHelper(IXmlParseHelper* const pIXmlParseHelper)
		{
			mHelperList.PushBack(pIXmlParseHelper);
		}

		void XmlParseMaster::RemoveHelper(IXmlParseHelper* const pIXmlParseHelper)
		{
			mHelperList.Remove(pIXmlParseHelper);
		}

		void XmlParseMaster::Parse(const char* pXmlString)
		{
			int size = strlen(pXmlString);
			if (XML_Parse(mParser, pXmlString, size, true) == 0)
			{
				int code = XML_GetErrorCode(mParser);
				const char *msg = (const char *)XML_ErrorString((XML_Error)code);
				fprintf(stderr, "Parsing error code %d message %s\n", code, msg);
			}
		}

		void XmlParseMaster::ParseFromFile(const char* pXmlFilePath)
		{
			std::ifstream fileStream(pXmlFilePath);
			std::string fileContent;

			// allocating the memory up front rather than relying string class's automatic reallocation
			fileStream.seekg(0, std::ios::end);
			fileContent.reserve(fileStream.tellg());
			fileStream.seekg(0, std::ios::beg);

			// reading file content
			fileContent.assign( (std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>() );

			Parse(fileContent.c_str());
		}

		const char* XmlParseMaster::GetFileName()
		{
			return mFilePath;
		}

		XmlParseMaster::SharedData* XmlParseMaster::GetSharedData()
		{
			return mSharedData;
		}

		void XmlParseMaster::SetSharedData(SharedData* const pSharedData)
		{
			mSharedData = pSharedData;
			mSharedData->SetXmlParseMaster(this);
		}

		void XmlParseMaster::StartElementHandler(void* pData, const XML_Char* pElement, const XML_Char** pAttributes)
		{
			XmlParseMaster* xmlParseMaster = reinterpret_cast<XmlParseMaster*>(pData);
			// implementing the chain of responsibility
			for (IXmlParseHelper* helper : xmlParseMaster->mHelperList)
			{
				if (helper->StartElementHandler(pData, pElement, pAttributes))
				{
					// if the helper process data then break
					break;
				}
			}

			xmlParseMaster->mSharedData->IncrementDepth();
		}

		void XmlParseMaster::EndElementHandler(void* pData, const XML_Char* pElement)
		{
			XmlParseMaster* xmlParseMaster = reinterpret_cast<XmlParseMaster*>(pData);
			// implementing the chain of responsibility
			for (IXmlParseHelper* helper : xmlParseMaster->mHelperList)
			{
				if (helper->EndElementHandler(pData, pElement))
				{
					// if the helper process data then break
					break;
				}
			}

			xmlParseMaster->mSharedData->DecrementDepth();
		}

		void XmlParseMaster::CharDataHandler(void* pData, const XML_Char* pElement, int pLength)
		{
			XmlParseMaster* xmlParseMaster = reinterpret_cast<XmlParseMaster*>(pData);
			// implementing the chain of responsibility
			for (IXmlParseHelper* helper : xmlParseMaster->mHelperList)
			{
				if (helper->CharDataHandler(pData, pElement, pLength))
				{
					// if the helper process data then break
					break;
				}
			}
		}
#pragma endregion
	}
}