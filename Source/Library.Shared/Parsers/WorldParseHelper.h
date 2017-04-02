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
				Constant tag and attribute values
			*/
			static const std::string sIntTag;
			static const std::string sFloatTag;
			static const std::string sStringTag;
			static const std::string sVec4Tag;
			static const std::string sMat4x4Tag;
			static const std::string sTableTag;
			static const std::string sKeyAttribute;
			static const std::string sValueAttribute;

			static const std::string sWorldTag;
			static const std::string sSectorTag;
			static const std::string sEntityTag;
			static const std::string sNameAttribute;
			static const std::string sEntityClassAttribute;

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
				True if the root element in the xml is named as world or else false.
			*/
			bool mHasValidRoot;

			/**
				If currently inside a sector
			*/
			bool mIsValidSector;

			/**
				If the entity is inside sector
			*/
			bool mIsValidEntity;

			/**
				If the element is table inside entity
			*/
			bool mIsTable;

		};
	}
}