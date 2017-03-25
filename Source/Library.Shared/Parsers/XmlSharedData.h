#pragma once
#include "XmlParseHelperTable.h"
#include "Container/Hashmap.h"
#include "XmlParseHelperConstruction.h"

namespace NoobEngine
{
	namespace Parsers
	{
		class XmlSharedData : public XmlParseHelperTable::XmlTableParser
		{
			friend class XmlParseHelperConstruction;
		public:
			/**
				@brief Default constructor.
			*/
			XmlSharedData();

			/**
				@brief Default destructor
			*/
			virtual ~XmlSharedData();

			/**
				@brief Create a clone of current XmlSharedData object and return the pointer as shared data.
				@return Pointer to SharedData that is a clone of this SharedData object.
			*/
			SharedData* Clone() const override;

		protected:
			/**
				All the prototype scopes that are made in construction will be in this 
			*/
			Container::Hashmap<std::string, Runtime::Scope*> mPrototypeScopes;

			/**
				Current prototype that is being processed.
			*/
			std::string mCurrentPrototype;
		};
	}
}