#include "pch.h"
#include "Attribute.h"

namespace NoobEngine
{
	namespace Runtime
	{
		RTTI_DEFINITIONS(Attribute)

		Container::Hashmap<uint64_t, Container::Vector<std::string>> Attribute::sAttributeList;

		Attribute::Attribute() : 
			Scope()
		{
			// adding this as prescribed attribute
			AppendPrescribedAttribute("this") = static_cast<RTTI*>(this);
		}

		Attribute::Attribute(const Attribute& pOther) : 
			Scope(pOther), mPrescribedAttributeCount(pOther.mPrescribedAttributeCount)
		{
			// adding this as prescribed attribute
			AppendPrescribedAttribute("this") = static_cast<RTTI*>(this);
		}

		Attribute& Attribute::operator=(const Attribute& pOther)
		{
			Scope::operator=(pOther);
			mPrescribedAttributeCount = pOther.mPrescribedAttributeCount;

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
		{}

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

		uint32_t Attribute::AuxiliaryBegin()
		{
			return mPrescribedAttributeCount;
		}

		Datum& Attribute::AppendPrescribedAttribute(std::string pKey)
		{
			if (IsPrescribedAttribute(pKey))
			{
				throw std::exception("Cannot append auxiliary attribute with prescribed key.");
			}

			if (!(sAttributeList[TypeIdClass()].Find(pKey) != sAttributeList[TypeIdClass()].end()))
			{
				// populate the prescribed attribute names
				sAttributeList[TypeIdClass()].PushBack(pKey);
			}

			mPrescribedAttributeCount++;

			// append a datum with key to scope and return the datum
			return Append(pKey);
		}

	}
}