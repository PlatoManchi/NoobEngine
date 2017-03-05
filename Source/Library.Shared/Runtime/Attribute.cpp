#include "pch.h"
#include "Attribute.h"

namespace NoobEngine
{
	namespace Runtime
	{
		RTTI_DEFINITIONS(Attribute)

		Attribute::Attribute()
		{

		}

		Attribute::Attribute(const Attribute & pOther)
		{}

		Attribute & Attribute::operator=(const Attribute & pOther)
		{
			// TODO: insert return statement here
			return *this;
		}
		
		Attribute::Attribute(const Attribute && pOther)
		{}

		Attribute & Attribute::operator=(const Attribute && pOther)
		{
			// TODO: insert return statement here
			return *this;
		}

		Attribute::~Attribute()
		{}

		bool Attribute::IsPrescribedAttribute(std::string pKey)
		{
			if (IsAttribute(pKey))
			{
				// TODO: Implementation
			}
			return false;
		}

		bool Attribute::IsAuxiliaryAttribute(std::string pKey)
		{
			if (IsAttribute(pKey))
			{
				// TODO: Implementation
			}
			return false;
		}

		bool Attribute::IsAttribute(std::string pKey)
		{
			return false;
		}

		Datum & Attribute::AppendAuxiliaryAttribute(std::string pKey)
		{
			// TODO: insert return statement here
			if (IsPrescribedAttribute(pKey))
			{
				throw std::exception("Cannot append auxiliary attribute with prescribed key.");
			}

			return Append(pKey);
		}

		uint32_t Attribute::AuxiliaryBegin()
		{
			return uint32_t();
		}
	}
}