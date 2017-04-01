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
		
		Attribute::Attribute(const Attribute&& pOther) :
			Scope(std::move(pOther))
		{
			// updating "this" prescribed attribute
			AppendPrescribedAttribute("this") = static_cast<RTTI*>(this);
		}

		Attribute& Attribute::operator=(const Attribute&& pOther)
		{
			if (this != &pOther)
			{
				Scope::operator=(std::move(pOther));
				// updating "this" prescribed attribute
				AppendPrescribedAttribute("this") = static_cast<RTTI*>(this);
			}
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

		bool Attribute::IsPrescribedAttribute(const std::string& pKey) const
		{
			if (IsAttribute(pKey))
			{
				uint64_t id = this->TypeIdInstance();
				id;
				return (sAttributeList[this->TypeIdInstance()].Find(pKey) != sAttributeList[this->TypeIdInstance()].end());
			}
			return false;
		}

		bool Attribute::IsAuxiliaryAttribute(const std::string& pKey) const
		{
			if (IsAttribute(pKey))
			{
				return !IsPrescribedAttribute(pKey);
			}
			return false;
		}

		bool Attribute::IsAttribute(const std::string& pKey) const
		{
			return (Find(pKey) != nullptr);
		}

		Datum& Attribute::AppendAuxiliaryAttribute(const std::string& pKey)
		{
			if (IsPrescribedAttribute(pKey))
			{
				throw std::exception("Cannot append auxiliary attribute with prescribed key.");
			}

			// append a datum with key to scope and return the datum
			return Append(pKey);
		}

		void Attribute::AppendNestedScope(const std::string& pKey, Scope& pValue)
		{
			Adopt(pValue, pKey);
			sAttributeList[this->TypeIdInstance()].PushBack(pKey);
		}
#pragma region AddInternalAttribute
		void Attribute::AddInternalAttribute(const std::string& pKey, int32_t pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}

		void Attribute::AddInternalAttribute(const std::string& pKey, float pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}

		void Attribute::AddInternalAttribute(const std::string& pKey, std::string& pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}

		void Attribute::AddInternalAttribute(const std::string& pKey, glm::vec4& pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}

		void Attribute::AddInternalAttribute(const std::string& pKey, glm::mat4x4& pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}

		void Attribute::AddInternalAttribute(const std::string& pKey, RTTI* pInitialValue)
		{
			AppendAuxiliaryAttribute(pKey) = pInitialValue;
		}
#pragma endregion
#pragma region AddExternalAttribute
		void Attribute::AddExternalAttribute(const std::string& pKey, int32_t* pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}

		void Attribute::AddExternalAttribute(const std::string& pKey, float* pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}

		void Attribute::AddExternalAttribute(const std::string& pKey, std::string* pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}

		void Attribute::AddExternalAttribute(const std::string& pKey, glm::vec4* pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}

		void Attribute::AddExternalAttribute(const std::string& pKey, glm::mat4x4* pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}

		void Attribute::AddExternalAttribute(const std::string& pKey, RTTI** pValue, uint32_t pSize)
		{
			AppendAuxiliaryAttribute(pKey).SetStorage(pValue, pSize);
		}
#pragma endregion
		Datum& Attribute::AppendPrescribedAttribute(const std::string& pKey)
		{
			if (IsAuxiliaryAttribute(pKey))
			{
				throw std::exception("Cannot append prescribed attribute with auxiliary key.");
			}

			Container::Vector<std::string>& attributeList = sAttributeList[this->TypeIdInstance()];
			if (attributeList.Find(pKey) == attributeList.end())
			{
				// populate the prescribed attribute names
				attributeList.PushBack(pKey);
			}

			// append a datum with key to scope and return the datum
			return Append(pKey);
		}

		void Attribute::Populate()
		{
			uint64_t thisClassIdInstance = this->TypeIdInstance();
			Container::Vector<std::string>& currentClassAttributeList = sAttributeList[thisClassIdInstance];
			for (std::pair<uint64_t, Container::Vector<std::string>>& element : sAttributeList)
			{
				if (element.first != thisClassIdInstance)
				{
					// check if the class that is being iterated is base of current class.
					if (this->Is(element.first))
					{
						// if searching class is a base class of current class
						// copy all prescribed attributes into current class attribute list
						Container::Vector<std::string>& baseClassAttributeList = sAttributeList[element.first];
						for (std::string& attribName : baseClassAttributeList)
						{
							if (currentClassAttributeList.Find(attribName) == currentClassAttributeList.end())
							{
								currentClassAttributeList.PushBack(attribName);
							}
						}
					}
				}
			}
		}

	}
}