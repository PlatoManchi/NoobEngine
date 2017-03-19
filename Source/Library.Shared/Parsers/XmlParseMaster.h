#pragma once

#include "Runtime/RTTI.h"
#include "Container/SList.h"
#include "IXmlParseHelper.h"
#include "expat.h"
//#include "expat_external.h"

namespace NoobEngine
{
	namespace Parsers
	{
		

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
			~XmlParseMaster();

			/**
				@brief Create a clone of current XmlParseMaster object and return the pointer for new XmlParseMaster that is cloned.
				@return Pointer to XmlParseMaster that is a clone of this XmlParseMaster object.
			*/
			XmlParseMaster* Clone();

			/**
				@brief Add the helper into list of xml parse helpers.
				@param pIXmlParseHelper Pointer to constant IXmlParseHelper object that needs to be added.
			*/
			void AddHelper(IXmlParseHelper* const pIXmlParseHelper);

			/**
				@brief Remove the helper from the list of xml parse helpers.
				@param pIXmlParseHelper Pointer to constant IXmlParseHelper object that needs to be removed.
			*/
			void RemoveHelper(IXmlParseHelper* const pIXmlParseHelper);

			/**
				@brief Parse the xml string using expat and call helpers as required.
				@details Throw exception if the pointer is nullptr.
				@param pXmlString Char pointer that has the xml data.
			*/
			void Parse(const char* pXmlString);

			/**
				@brief Read the data from xml file and parse the xml.
				@details Throw exception if the pointer is nullptr.
				@param pXmlFilePath Char pointer that has name of the file to parse.
			*/
			void ParseFromFile(const char* pXmlFilePath);

			/**
				@brief Returns the path for the file being parsed.
				@return Char pointer that holds the path for file being parsed.
			*/
			const char* GetFileName();

			/**
				@brief Return the SharedData that this XmlParseMaster has.
				@return Pointer to the SharedData.
			*/
			SharedData* GetSharedData();

			/**
				@brief Set SharedData that his XmlParseMaster has.
				@param pSharedData Pointer to SharedData.
			*/
			void SetSharedData(SharedData* const pSharedData);

		private:
			/**
				Holds the path to Xml file that is currently being parsed.
			*/
			char* mFilePath;

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
				@brief Callback that expat will call to handle XML start element.
				@param pData
				@param pElement String that represents the element.
				@param pAttributes Array of Attribute to value pairs
			*/
			static void StartElementHandler(void* pData, const XML_Char* pElement, const XML_Char** pAttributes);

			/**
				@brief Callback that expat will call to handle XML end element.
				@param pData
				@param pElement String that represents the element.
			*/
			static void EndElementHandler(void* pData, const XML_Char* pElement);


			static void CharDataHandler(void* pData, const XML_Char* pElement, int pLength);
		};
	}
}

