#pragma once

#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "Runtime/Scope.h"

namespace NoobEngine
{
	namespace Parsers
	{
		/**
			This helper will handle the XML grammar by parsing it and creating a heap allocated Scope object. The scope that is created by parsing should be explicitly deleted otherwise leads to memory leak.

		*/
		class XmlParseHelperTable : public IXmlParseHelper
		{
		public:
			/**
				XmlTableParser that extends XmlParseMaster::SharedData that will be used as the shared data for this helper.
			*/
			class XmlTableParser : public XmlParseMaster::SharedData
			{
				RTTI_DECLARATIONS(XmlTableParser, XmlParseMaster::SharedData)

				friend class XmlParseHelperTable;

			public:
				/**
					@brief Default constructor.
				*/
				XmlTableParser();

				/**
					@brief Default destructor
				*/
				virtual ~XmlTableParser();

				/**
					@brief Create a clone of current XmlTableParser object and return the pointer as shared data.
					@return Pointer to SharedData that is a clone of this SharedData object.
				*/
				SharedData* Clone() const override;

				/**
					@brief Returns the scope that points to root node int he XML.
					@return Scope reference.
				*/
				Runtime::Scope& GetRootNode() const;

				/**
					@brief Return the scope that is currently being manipulated.
					@return Scope reference
				*/
				Runtime::Scope& GetCurrentNode() const;

			protected:
				/**
					If the xml has valid root
				*/
				bool mHasValidRoot;

				/**
					Scope that points to the root node.
				*/
				Runtime::Scope* mRoot;

				/**
					Scope that points to the node that is currently being manipulated.
					This will always be mRoot node or a child of mRoot.
				*/
				Runtime::Scope* mCurrentRoot;

				/**
					If the data that is being pushed is an array then this is a counter for the index.
				*/
				uint32_t mArrayIndex;

				/**
					Current tag that is processed
				*/
				std::string mCurrentTag;

				/**
					If the parsing is in construction phase or not
				*/
				bool mIsConstructionPhase;

				/**
					If the table is using existing prototype
				*/
				bool mIsPrototypeTable;
			};

			/**
				@brief Default constructor
			*/
			XmlParseHelperTable();

			/**
				@brief Default destructor.
			*/
			virtual ~XmlParseHelperTable();

			/**
				@brief Initialize this helper. This will get called just before each file is parsed.
				@param[in] pXmlParseMaster The XmlParseMaster that this helper is attached to.
				@exception std::exception Throws exception if the SharedData that the XmlParseMaster has SharedData that is not of type XmlTableParser.
			*/
			virtual void Initialize(XmlParseMaster& pXmlParseMaster) override;

			/**
				@brief Called every time a start element tag is hit in the XML.
				@param[in] pElement String that holds the element
				@param[in] pAttributes Hashmap that holds all the attributes.
			*/
			virtual bool StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes) override;

			/**
				@brief Called every time a end of the element is reached in the XML.
				@param[in] pElement String that holds the element.
			*/
			virtual bool EndElementHandler(const std::string& pElement) override;

			/**
				@brief Create a clone of XmlParseHelper and return the pointer to the clone.
				@return IXmlParseHelper pointer that points to the new cloned parse helper.
			*/
			virtual IXmlParseHelper* Clone() const override;

		protected:
			/**
				True if the root element in the xml is named as root or else false.
			*/
			bool mHasValidRoot;
		};
	}
}