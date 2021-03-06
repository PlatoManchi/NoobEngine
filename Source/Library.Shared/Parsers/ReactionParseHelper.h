#pragma once
#include "IXmlParseHelper.h"

namespace NoobEngine
{
	namespace Parsers
	{
		class ReactionParseHelper : public IXmlParseHelper
		{
		public:
			/**
				Constant tag and attribute values
			*/
			static const std::string sActionEventTag;
			static const std::string sReactionTag;
			static const std::string sKeyAttribute;
			static const std::string sSubtypeAttribute;
			static const std::string sDelayAttribute;

			/**
				@brief Default constructor
			*/
			ReactionParseHelper();

			/**
				@brief Default destructor
			*/
			~ReactionParseHelper();

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

		private:
			/**
				if ActionEvent
			*/
			bool mIsValidActionEvent;

			/**
				if Reaction
			*/
			bool mIsValidReaction;
		};
	}
}