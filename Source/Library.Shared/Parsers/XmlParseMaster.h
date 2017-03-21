#pragma once

#include "Runtime/RTTI.h"
#include "Container/SList.h"
#include "IXmlParseHelper.h"
#include "expat.h"

namespace NoobEngine
{
	namespace Parsers
	{
		class IXmlParseHelper;

		/**
			Parse the xml file using Expat.
			Each XmlParseMaster will have a SharedData associated with it and every SharedData will have a XmlParseMaster that is associated to.
		*/
		class XmlParseMaster
		{
			
		public:
			/**
				Inner class that holds the data shared between IXmlParseHelper objects
			*/
			class SharedData : public NoobEngine::Runtime::RTTI
			{
				friend class XmlParseMaster;

				RTTI_DECLARATIONS(SharedData, NoobEngine::Runtime::RTTI)
			public:
				/**
					@brief Default constructor
				*/
				SharedData();

				/**
					@brief Create a clone of current shared data object and return the pointer for shared data.
					@return Pointer to SharedData that is a clone of this SharedData object.
				*/
				SharedData* Clone() const;

				/**
					@brief Sets the XmlParseMaster that this SharedData belongs to.
					@param pXmlParseMaster Pointer to constant XmlParseMaster.
				*/
				void SetXmlParseMaster(XmlParseMaster* const pXmlParseMaster);

				/**
					@brief Get the XmlParseMaster that his SharedData belongs to.
					@return Pointer to XmlParseMaster
				*/
				XmlParseMaster* GetXmlParseMaster() const;

				/**
					@brief Return the current Depth.
				*/
				uint32_t Depth() const;
			private:
				/**
					Pointer to XmlParseMaster that this SharedData belongs to.
				*/
				XmlParseMaster* mXmlParseMaster;

				/**
					Depth at which current xml parsing is happening. If Depth is 0 that means the element is root element.
				*/
				uint32_t mDepth;

				/**
					@brief Increase the depth by 1
				*/
				void IncrementDepth();

				/**
					@brief Decrement the depth by 1
				*/
				void DecrementDepth();
			};
			
			/**
				@brief Default constructor
			*/
			XmlParseMaster();

			/**
				@brief Default destructor
			*/
			virtual ~XmlParseMaster();

			/**
				@brief Create a clone of current XmlParseMaster object and return the pointer for new XmlParseMaster that is cloned.
				@return Pointer to XmlParseMaster that is a clone of this XmlParseMaster object.
			*/
			XmlParseMaster* Clone() const;

			/**
				@brief Add the helper into list of xml parse helpers.
				@param[in] pIXmlParseHelper Pointer to constant IXmlParseHelper object that needs to be added.
				@exception std::exception If this XmlParseMaster is cloned then exception is thrown.
			*/
			void AddHelper(IXmlParseHelper& pIXmlParseHelper);

			/**
				@brief Remove the helper from the list of xml parse helpers.
				@param[in] pIXmlParseHelper Pointer to constant IXmlParseHelper object that needs to be removed.
				@exception std::exception If this XmlParseMaster is cloned then exception is thrown.
			*/
			void RemoveHelper(IXmlParseHelper& pIXmlParseHelper);

			/**
				@brief Parse the xml string using expat and call helpers as required.
				@details Throw exception if the pointer is nullptr.
				@param[in] pXmlString Char pointer that has the xml data.
				@exception std::exception Invalid pXmlString
			*/
			void Parse(const char* pXmlString);

			/**
				@brief Read the data from xml file and parse the xml.
				@details Throw exception if the pointer is nullptr.
				@param[in] pXmlFilePath Char pointer that has name of the file to parse.
				@exception std::exception Invalid filename.
			*/
			void ParseFromFile(const char* pXmlFilePath);

			/**
				@brief Returns the path for the file being parsed.
				@return String that holds the path for file being parsed.
			*/
			std::string GetFileName() const;

			/**
				@brief Return the SharedData that this XmlParseMaster has.
				@return Pointer to the SharedData.
			*/
			SharedData* GetSharedData() const;

			/**
				@brief Set SharedData that his XmlParseMaster has.
				@param[in] pSharedData Pointer to SharedData.
			*/
			void SetSharedData(SharedData& pSharedData);

		private:
			/**
				Holds if this XmlParseMaster is clone or not
			*/
			bool mIsClone;
			/**
				Holds the path to Xml file that is currently being parsed.
			*/
			std::string mFilePath;

			/**
				Pointer to the SharedData that this XmlParseMaster has.
			*/
			SharedData* mSharedData;

			/**
				XML_Parser object from expat
			*/
			XML_Parser mParser;

			/**
				Holds the list of all the IXmlParseHelper that are registered with this XmlParseMaster.
			*/
			Container::SList<IXmlParseHelper*> mHelperList;

			/**
				Holds the helper that recently successfully server the request
			*/
			IXmlParseHelper* mRecentHelper;

			/**
				@brief Callback that expat will call to handle XML start element.
				@param[in] pData The user data that is set in expat.
				@param[in] pElement String that represents the element.
				@param[in] pAttributes Array of Attribute to value pairs.
			*/
			static void StartElementHandler(void* pData, const XML_Char* pElement, const XML_Char** pAttributes);

			/**
				@brief Callback that expat will call to handle XML end element.
				@param[in] pData The user data that is set in expat.
				@param[in] pElement String that represents the element.
			*/
			static void EndElementHandler(void* pData, const XML_Char* pElement);

			/**
				@brief Callback that expat will call to handle characters in between tags.
				@param[in] pData The user data that is set in expat.
				@param[in] pCharValue The characters in between tags.
				@param[in] pLength Number of characters.
			*/
			static void CharDataHandler(void* pData, const XML_Char* pCharValue, int pLength);
		};
	}
}

