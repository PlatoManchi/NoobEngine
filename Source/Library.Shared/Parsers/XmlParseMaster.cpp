#include "pch.h"
#include "XmlParseMaster.h"
#include "Container/Hashmap.h"
#include "Utils/Utils.h"

namespace NoobEngine
{
	namespace Parsers
	{
		
#pragma region SharedData
		RTTI_DEFINITIONS(XmlParseMaster::SharedData)

		XmlParseMaster::SharedData::SharedData():
			mDepth(0)
		{

		}

		XmlParseMaster::SharedData::~SharedData()
		{
		}

		XmlParseMaster::SharedData* XmlParseMaster::SharedData::Clone() const
		{
			XmlParseMaster::SharedData* cloneSharedData = new XmlParseMaster::SharedData();
			return cloneSharedData;
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
			if (mDepth > 0)
			{
				--mDepth;
			}
		}

		uint32_t XmlParseMaster::SharedData::Depth() const
		{
			return mDepth;
		}
#pragma endregion
#pragma region XmlParseMaster
		XmlParseMaster::XmlParseMaster() : 
			mParser(XML_ParserCreate(nullptr)), mFilePath(""), mSharedData(nullptr), mRecentHelper(nullptr), mIsClone(false)
		{
			XML_SetUserData(mParser, this);
			XML_SetElementHandler(mParser, &XmlParseMaster::StartElementHandler, &XmlParseMaster::EndElementHandler);
			XML_SetCharacterDataHandler(mParser, &XmlParseMaster::CharDataHandler);
		}

		XmlParseMaster::~XmlParseMaster()
		{
			XML_ParserFree(mParser);
			if (mIsClone) 
			{
				delete mSharedData;
				for (IXmlParseHelper* helper : mHelperList)
				{
					delete helper;
				}
			}
		}

		XmlParseMaster* XmlParseMaster::Clone() const
		{
			XmlParseMaster* cloneMaster = new XmlParseMaster();
			
			cloneMaster->SetSharedData( *(mSharedData->Clone()) );

			for (IXmlParseHelper* helpers : mHelperList)
			{
				cloneMaster->AddHelper( *(helpers->Clone()) );
			}

			cloneMaster->mIsClone = true;
			return cloneMaster;
		}

		void XmlParseMaster::AddHelper(IXmlParseHelper& pIXmlParseHelper)
		{
			if (mIsClone)
			{
				throw std::exception("Cannot add helper to cloned XmlParseMaster.");
			}

			if (mHelperList.Find(&pIXmlParseHelper) == mHelperList.end())
			{
				mHelperList.PushBack(&pIXmlParseHelper);
			}
		}

		void XmlParseMaster::RemoveHelper(IXmlParseHelper& pIXmlParseHelper)
		{
			if (mIsClone)
			{
				throw std::exception("Cannot remove helper from cloned XmlParseMaster.");
			}
			mHelperList.Remove(&pIXmlParseHelper);
		}

		void XmlParseMaster::Parse(const char* pXmlString)
		{
			if (!pXmlString)
			{
				throw std::exception("pXmlString cannot be nullptr.");
			}

			// reset expat
			Reset();

			for (IXmlParseHelper* helper : mHelperList)
			{
				helper->Initialize(this);
			}

			size_t size = strlen(pXmlString);
			if (XML_Parse(mParser, pXmlString, static_cast<int>(size), true) == 0)
			{
				std::stringstream errorMsg;
				int code = XML_GetErrorCode(mParser);
				const char *msg = (const char *)XML_ErrorString((XML_Error)code);
				errorMsg << "Parsing error code '" << code << "' message '" << msg << "'" << NULL;
				throw std::exception(errorMsg.str().c_str());
			}
		}

		void XmlParseMaster::ParseFromFile(const char* pXmlFilePath)
		{
			if (!pXmlFilePath)
			{
				throw std::exception("pXmlFilePath cannot be nullptr.");
			}

			// opening file stream
			std::ifstream fileStream(pXmlFilePath);
			
			if (!fileStream) {
				fileStream.close();
				// if the file path is invalid
				std::string exceptionStr = "File path \"" + std::string(pXmlFilePath) + "\" is invalid.";
				throw exception(exceptionStr.c_str());
			}

			// if valid file path and file
			mFilePath = pXmlFilePath;
			std::string fileContent;

			// allocating the memory up front rather than relying string class's automatic reallocation
			fileStream.seekg(0, std::ios::end);
			fileContent.reserve(static_cast<size_t>(fileStream.tellg()));
			fileStream.seekg(0, std::ios::beg);

			// reading file content
			fileContent.assign( (std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>() );

			// close file stream
			fileStream.close();

			Parse(fileContent.c_str());
		}

		std::string XmlParseMaster::GetFileName() const
		{
			return mFilePath;
		}

		XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const
		{
			return mSharedData;
		}

		void XmlParseMaster::SetSharedData(SharedData& pSharedData)
		{
			if (mIsClone)
			{
				throw exception("Cannot change the shared data of clone XmlParseMaster.");
			}
			mSharedData = &pSharedData;
			mSharedData->SetXmlParseMaster(this);
		}

		void XmlParseMaster::StartElementHandler(void* pData, const XML_Char* pElement, const XML_Char** pAttributes)
		{
			XmlParseMaster* xmlParseMaster = reinterpret_cast<XmlParseMaster*>(pData);

			// increment depth
			if (xmlParseMaster->mSharedData)
			{
				xmlParseMaster->mSharedData->IncrementDepth();
			}

			if (xmlParseMaster->mHelperList.Size() != 0)
			{
				// converting the data into easy to access data types
				std::string element = Utils::ToLower(pElement);
				NoobEngine::Container::Hashmap<std::string, std::string> attributeValuePair;

				uint32_t index = 0;
				while (pAttributes[index])
				{
					std::string name = Utils::ToLower(std::string(pAttributes[index++]));
					std::string value = std::string(pAttributes[index++]);

					attributeValuePair[name] = value;
				}

				// implementing the chain of responsibility
				for (IXmlParseHelper* helper : xmlParseMaster->mHelperList)
				{
					if (helper->StartElementHandler(element, attributeValuePair))
					{
						// if the helper process data then break
						xmlParseMaster->mRecentHelper = helper;
						break;
					}
				}
			}
		}

		void XmlParseMaster::EndElementHandler(void* pData, const XML_Char* pElement)
		{
			XmlParseMaster* xmlParseMaster = reinterpret_cast<XmlParseMaster*>(pData);
			if (xmlParseMaster->mHelperList.Size() != 0)
			{
				std::string element = Utils::ToLower(pElement);
				// implementing the chain of responsibility
				for (IXmlParseHelper* helper : xmlParseMaster->mHelperList)
				{
					
					if (helper->EndElementHandler(element))
					{
						// if the helper process data then break
						break;
					}
				}
			}
			
			// decrement the depth
			if (xmlParseMaster->mSharedData)
			{
				xmlParseMaster->mSharedData->DecrementDepth();
			}
		}

		void XmlParseMaster::CharDataHandler(void* pData, const XML_Char* pCharValue, int pLength)
		{
			XmlParseMaster* xmlParseMaster = reinterpret_cast<XmlParseMaster*>(pData);
			
			if (xmlParseMaster->mHelperList.Size() != 0)
			{
				// converting to string
				std::string stringValue(reinterpret_cast<const char*>(pCharValue), pLength);
				if (xmlParseMaster->mRecentHelper)
				{
					xmlParseMaster->mRecentHelper->CharDataHandler(stringValue);
				}
			}// end of if
		}

		void XmlParseMaster::Reset()
		{
			XML_ParserReset(mParser, nullptr);
			XML_SetUserData(mParser, this);
			XML_SetElementHandler(mParser, &XmlParseMaster::StartElementHandler, &XmlParseMaster::EndElementHandler);
			XML_SetCharacterDataHandler(mParser, &XmlParseMaster::CharDataHandler);
		}

		
#pragma endregion
	}
}