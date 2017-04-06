#pragma once
#include "IXmlParseHelper.h"

namespace NoobEngine
{
	namespace Parsers
	{
		class ActionParseHelper : public IXmlParseHelper
		{
		public:
			/**
				Constant tag and attribute values
			*/
			static const std::string sActionTag;
			static const std::string sConditionAttribute;
			static const std::string sClassAttribute;
			static const std::string sKeyAttribute;
			static const std::string sValueAttribute;

			// if
			static const std::string sIfTag;
			static const std::string sThenTag;
			static const std::string sElseTag;

			// switch
			static const std::string sSwitchTag;
			static const std::string sValueTag;

			// while
			static const std::string sWhileTag;

			// for each
			static const std::string sForEachTag;

			// decrement
			static const std::string sDecrementTag;

			// create action
			static const std::string sCreateActionTag;

			// destroy action
			static const std::string sDestroyActionTag;

			/**
				@brief Default constructor
			*/
			ActionParseHelper();

			/**
				@brief Default destructor
			*/
			~ActionParseHelper();

			/**
				@brief Initialize this helper. This will get called just before each file is parsed.
				@param[in] pXmlParseMaster The XmlParseMaster that this helper is attached to.
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
				Actions can contain actions. So to make sure that they are processed correctly,
				instead of a bool, the helper will keep track of the depth of the actions.
				if depth is 0 then its out of action.
			*/
			uint32_t mActionDepth;

			bool mIsValidIf;
		};
	}
}