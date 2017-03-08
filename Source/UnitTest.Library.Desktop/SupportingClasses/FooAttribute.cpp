#include "pch.h"
#include "FooAttribute.h"

namespace SupportingClasses
{
	FooAttribute::FooAttribute() : Attribute()
	{
		mHealth = 100;
		mRegen = 0.5f;
		mName = "FooAttribute";
		mPos = glm::vec4();

		Populate();
	}

	FooAttribute::FooAttribute(const FooAttribute& pOther) :
		FooAttribute()
	{
		operator=(pOther);
	}

	void FooAttribute::ExceptionAddingPrescribed()
	{
		AppendAuxiliaryAttribute("Aux") = 10;
		AppendPrescribedAttribute("Aux");
	}

	FooAttribute & FooAttribute::operator=(const FooAttribute & pOther)
	{
		if (this != &pOther)
		{
			Attribute::operator=(pOther);

			mName = pOther.mName;
			mHealth = pOther.mHealth;
			mRegen = pOther.mRegen;
			mPos = pOther.mPos;

			Populate();
		}
		
		return *this;
	}

	void FooAttribute::Populate()
	{
		AppendPrescribedAttribute("Health").SetStorage(&mHealth, 1);
		AppendPrescribedAttribute("Regen").SetStorage(&mRegen, 1);
		AppendPrescribedAttribute("Name").SetStorage(&mName, 1);
		AppendPrescribedAttribute("Pos").SetStorage(&mPos, 1);
	}
}