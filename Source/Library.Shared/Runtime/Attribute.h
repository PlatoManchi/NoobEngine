#pragma once
#include "RTTI.h"
#include "Datum.h"
#include "Scope.h"

namespace NoobEngine
{
	namespace Runtime
	{
		class Attribute : public Scope
		{
			RTTI_DECLARATIONS(Attribute, Scope)
		public:
			/**
				@brief Default constructor.
			*/
			Attribute();

			/**
				@brief Copy constructor that takes the attribute as parameter and deep copy everything.
				@param pOther The attribute that should be copied.
				@see Attribute()
			*/
			Attribute(const Attribute& pOther);

			/**
				@brief Deep copy all content from passed attribute into current attribute
				@param pOther The attribute from which copy should be made
				@see operator=()
			*/
			Attribute& operator=(const Attribute& pOther);

			/**
				@brief Move semantics. Steals the data from passed attribute and nullify the passed attribute.
				@param pOther Attribute from which to steal the data.
			*/
			Attribute(const Attribute&& pOther);

			/**
				@brief Move semantics. Steal the data from passed attribute and nullify the passed attribute.
				@param pOther Attribute from which to steal the data.
			*/
			Attribute& operator=(const Attribute&& pOther);

			/**
				@brief Standard destructor
			*/
			virtual ~Attribute();

			/**
				@brief Checks if the attribute is prescribed and if yes then return true else false.
				@param pKey String that holds the key for the attribute.
				@return Boolean which is true if pKey is key of prescribed attribute else false.
				@see IsAuxiliaryAttribute()
				@see IsAttribute()
			*/
			bool IsPrescribedAttribute(std::string pKey);

			/**
				@brief Checks if the attribute is auxiliary and if yes then return true else false.
				@param pKey String that holds the key for the attribute.
				@return Boolean which is true if pKey is key of auxiliary attribute else false.
				@see AppendAuxiliaryAttribute()
				@see IsPrescribedAttribute()
				@see IsAttribute()
			*/
			bool IsAuxiliaryAttribute(std::string pKey);

			/**
				@brief Checks if there is attribute with key and return true if present else false.
				@param pKey String that holds the key for the attribute.
				@return Boolean which is true if pKey is a key to attribute else false.
				@see IsAuxiliaryAttribute()
				@see IsPrescribedAttribute()
			*/
			bool IsAttribute(std::string pKey);

			/**
				@brief Adds an auxiliary attribute to the attribute
				@param pKey The key to be used for the attribute
				@return Reference to datum that is appended
			*/
			Datum& AppendAuxiliaryAttribute(std::string pKey);

			/**
				@brief Returns the position of the auxiliary attributes in the map
				@return Unsigned int that holds the value of start of auxiliary attributes.
			*/
			uint32_t AuxiliaryBegin();
		protected:
			void AddPrescribedAttribute();
		private:
			
		};
	}
}