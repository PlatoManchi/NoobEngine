#include "pch.h"
#include "Attribute.h"

namespace NoobEngine
{
	namespace Runtime
	{
		RTTI_DEFINITIONS(Attribute)

		Container::Hashmap<uint64_t, Container::Vector<std::string>> Attribute::sAttributeList;
		uint32_t Attribute::mObjCount = 0;

		Attribute::Attribute() : 
			Scope()
		{
			++mObjCount;
			// adding this as prescribed attribute
			AppendPrescribedAttribute("this") = static_cast<RTTI*>(this);
		}

		Attribute::Attribute(const Attribute& pOther) : 
			Scope(pOther)
		{
			++mObjCount;

			// updating "this" prescribed attribute
			AppendPrescribedAttribute("this") = static_cast<RTTI*>(this);
		}

		Attribute& Attribute::operator=(const Attribute& pOther)
		{
			if (this != &pOther)
			{
				Scope::operator=(pOther);

				// updating "this" prescribed attribute
				AppendPrescribedAttribute("this") = static_cast<RTTI*>(this);
			}
			
			return *this;
		}
		
		Attribute::Attribute(const Attribute&& pOther)
		{
			// TODO: implement move semantics
			pOther;
		}

		Attribute & Attribute::operator=(const Attribute&& pOther)
		{
			// TODO: insert return statement here
			pOther;
			return *this;
		}

		Attribute::~Attribute()
		{
			--mObjCount;
			if (mObjCount == 0)
			{
				sAttributeList.Clear();
			}
		}

		bool Attribute::IsPrescribedAttribute(std::string pKey)
		{
			if (IsAttribute(pKey))
			{
				return (sAttributeList[TypeIdClass()].Find(pKey) != sAttributeList[TypeIdClass()].end());
			}
			return false;
		}

		bool Attribute::IsAuxiliaryAttribute(std::string pKey)
		{
			if (IsAttribute(pKey))
			{
				return !IsPrescribedAttribute(pKey);
			}
			return false;
		}

		bool Attribute::IsAttribute(std::string pKey)
		{
			return (Find(pKey) != nullptr);
		}

		Datum& Attribute::AppendAuxiliaryAttribute(std::string pKey)
		{
			if (IsPrescribedAttribute(pKey))
			{
				throw std::exception("Cannot append auxiliary attribute with prescribed key.");
			}

			// append a datum with key to scope and return the datum
			return Append(pKey);
		}

		void Attribute::AppendNestedScope(std::string pKey, Scope& pValue)
		{
			if (IsAttribute(pKey))
			{
				throw std::exception("Key already exists.");
			}

			Adopt(pValue, pKey);
			sAttributeList[TypeIdClass()].PushBack(pKey);
		}
#pragma region AddInternalAttribute
		void Attribute::AddInternalAttribute(std::string pKey, int32_t pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}

		void Attribute::AddInternalAttribute(std::string pKey, float pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}

		void Attribute::AddInternalAttribute(std::string pKey, std::string& pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}

		void Attribute::AddInternalAttribute(std::string pKey, glm::vec4& pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}

		void Attribute::AddInternalAttribute(std::string pKey, glm::mat4x4& pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}

		void Attribute::AddInternalAttribute(std::string pKey, RTTI* pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}
#pragma endregion
#pragma region AddExternalAttribute
		void Attribute::AddExternalAttribute(std::string pKey, int32_t * pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}

		void Attribute::AddExternalAttribute(std::string pKey, float * pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}

		void Attribute::AddExternalAttribute(std::string pKey, std::string * pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}

		void Attribute::AddExternalAttribute(std::string pKey, glm::vec4 * pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}

		void Attribute::AddExternalAttribute(std::string pKey, glm::mat4x4 * pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}

		void Attribute::AddExternalAttribute(std::string pKey, RTTI ** pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}
#pragma endregion
		Datum& Attribute::AppendPrescribedAttribute(std::string pKey)
		{
			if (IsAuxiliaryAttribute(pKey))
			{
				throw std::exception("Cannot append prescribed attribute with auxiliary key.");
			}

			if (sAttributeList[TypeIdClass()].Find(pKey) == sAttributeList[TypeIdClass()].end())
			{
				// populate the prescribed attribute names
				sAttributeList[TypeIdClass()].PushBack(pKey);
			}

			// append a datum with key to scope and return the datum
			return Append(pKey);
		}

	}
}