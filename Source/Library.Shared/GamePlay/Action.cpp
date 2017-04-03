#include "pch.h"
#include "Action.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		const std::string Action::sActionKey = "action";

		Action::Action() :
			Attribute(), mParent(nullptr)
		{
			Populate();
		}

		Action::~Action()
		{
		}

		std::string Action::Name()
		{
			return mName;
		}

		void Action::SetName(std::string pName)
		{
			mName = pName;
		}

		Runtime::Attribute& Action::GetParent() const
		{
			assert(mParent != nullptr);

			return *mParent;
		}

		void Action::SetParent(Attribute& pParent)
		{
			assert(pParent.Is(World::TypeIdClass()) || pParent.Is(Sector::TypeIdClass()) || pParent.Is(Entity::TypeIdClass()));

			if (mParent != &pParent)
			{
				pParent.Adopt(*this, Action::sActionKey);
				mParent = &pParent;
			}
		}

		void Action::Populate()
		{
			Attribute::Populate();
		}
	}
}