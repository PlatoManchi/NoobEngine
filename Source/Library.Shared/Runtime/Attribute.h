#pragma once
#include "RTTI.h"
#include "Datum.h"
#include "Scope.h"
#include "Container/Hashmap.h"

namespace NoobEngine
{
	namespace Runtime
	{
		class Attribute abstract : public Scope
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
			bool IsPrescribedAttribute(const std::string& pKey) const;

			/**
				@brief Checks if the attribute is auxiliary and if yes then return true else false.
				@param pKey String that holds the key for the attribute.
				@return Boolean which is true if pKey is key of auxiliary attribute else false.
				@see AppendAuxiliaryAttribute()
				@see IsPrescribedAttribute()
				@see IsAttribute()
			*/
			bool IsAuxiliaryAttribute(const std::string& pKey) const;

			/**
				@brief Checks if there is attribute with key and return true if present else false.
				@param pKey String that holds the key for the attribute.
				@return Boolean which is true if pKey is a key to attribute else false.
				@see IsAuxiliaryAttribute()
				@see IsPrescribedAttribute()
			*/
			bool IsAttribute(const std::string& pKey) const;

			/**
				@brief Adds an auxiliary attribute to the attribute
				@param pKey The key to be used for the attribute
				@return Reference to datum that is appended
			*/
			Datum& AppendAuxiliaryAttribute(const std::string& pKey);

			/**
				@brief Appends a nested scope to the current scope.
				@details This will adopt the scope as a prescribed scope. Will throw exception if key already exists.
				@param pKey string that holds value of key.
				@param pValue Reference to scope that has to be adopted.
			*/
			void AppendNestedScope(const std::string& pKey, Scope& pValue);

			/**
				@brief Add the attribute as internal attribute and initialize that value with the value sent.
				@param pKey String that holds that value of key.
				@param pInitialValue The initial value of the attribute.
			*/
			void AddInternalAttribute(const std::string& pKey, int32_t pInitialValue);

			/**
				@brief Add the attribute as internal attribute and initialize that value with the value sent.
				@param pKey String that holds that value of key.
				@param pInitialValue The initial value of the attribute.
			*/
			void AddInternalAttribute(const std::string& pKey, float pInitialValue);

			/**
				@brief Add the attribute as internal attribute and initialize that value with the value sent.
				@param pKey String that holds that value of key.
				@param pInitialValue The initial value of the attribute.
			*/
			void AddInternalAttribute(const std::string& pKey, std::string& pInitialValue);

			/**
				@brief Add the attribute as internal attribute and initialize that value with the value sent.
				@param pKey String that holds that value of key.
				@param pInitialValue The initial value of the attribute.
			*/
			void AddInternalAttribute(const std::string& pKey, glm::vec4& pInitialValue);

			/**
				@brief Add the attribute as internal attribute and initialize that value with the value sent.
				@param pKey String that holds that value of key.
				@param pInitialValue The initial value of the attribute.
			*/
			void AddInternalAttribute(const std::string& pKey, glm::mat4x4& pInitialValue);

			/**
				@brief Add the attribute as internal attribute and initialize that value with the value sent.
				@param pKey String that holds that value of key.
				@param pInitialValue The initial value of the attribute.
			*/
			void AddInternalAttribute(const std::string& pKey, RTTI* pInitialValue);

			/**
				@brief Add the attribute as external attribute.
				@param pKey String that holds that value of key.
				@param pValue The value to hold.
			*/
			void AddExternalAttribute(const std::string& pKey, int32_t* pValue, uint32_t pSize = 1);

			/**
				@brief Add the attribute as external attribute.
				@param pKey String that holds that value of key.
				@param pValue The value to hold.
			*/
			void AddExternalAttribute(const std::string& pKey, float* pValue, uint32_t pSize = 1);

			/**
				@brief Add the attribute as external attribute.
				@param pKey String that holds that value of key.
				@param pValue The value to hold.
			*/
			void AddExternalAttribute(const std::string& pKey, std::string* pValue, uint32_t pSize = 1);

			/**
				@brief Add the attribute as external attribute.
				@param pKey String that holds that value of key.
				@param pValue The value to hold.
			*/
			void AddExternalAttribute(const std::string& pKey, glm::vec4* pValue, uint32_t pSize = 1);

			/**
				@brief Add the attribute as external attribute.
				@param pKey String that holds that value of key.
				@param pValue The value to hold.
			*/
			void AddExternalAttribute(const std::string& pKey, glm::mat4x4* pValue, uint32_t pSize = 1);

			/**
				@brief Add the attribute as external attribute.
				@param pKey String that holds that value of key.
				@param pValue The value to hold.
			*/
			void AddExternalAttribute(const std::string& pKey, RTTI** pValue, uint32_t pSize = 1);

		protected:
			/**
				@brief Add prescribed attribute
				@param pKey The key to be used for the attribute
				@return Reference to datum that is appended. If key already exists returns existing datum else creates new datum.
			*/
			Datum& AppendPrescribedAttribute(const std::string& pKey);

			/**
				@brief Populate all the initial prescribed and auxiliary attributes.
				@details This function has to be called in all child class constructors. Failing to do so will leads to unexpected behavior.
			*/
			void Populate() {};
		private:
			
			static uint32_t mObjCount;

			/**
				Static HashMap that holds the prescribed attribute list of all the class that will extend Attribute
			*/
			static Container::Hashmap<uint64_t, Container::Vector<std::string>> sAttributeList;
		};
	}
}