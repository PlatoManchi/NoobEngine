#pragma once
#include "Runtime/Attribute.h"

namespace SupportingClasses
{
	class FooAttribute : public NoobEngine::Runtime::Attribute
	{
	public:
		FooAttribute();
		FooAttribute(const FooAttribute& pOther);

		int mHealth;
		float mRegen;
		std::string mName;
		glm::vec4 mPos;

		void ExceptionAddingPrescribed();

		FooAttribute& operator=(const FooAttribute& pOther);

	protected:
		void Populate();
	private:
		

		
	};
}