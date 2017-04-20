#include "pch.h"
#include "Action.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "ActionList.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(Action)

		const char* Action::sActionKey = "action";
		const char* Action::sKeyAttribute = "key";
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

		void Action::SetParent(ActionList& pParent)
		{
			assert(pParent->Is(ActionList::TypeIdClass()));

			if (mParent != &pParent)
			{
				pParent.Adopt(*this, ActionList::sActionListKey);
				mParent = static_cast<Attribute*>(&pParent);
			}
		}

		void Action::SetParent(Entity& pParent)
		{
			SetParent(&pParent);
		}

		void Action::SetParent(Sector& pParent)
		{
			SetParent(&pParent);
		}

		void Action::SetParent(World& pParent)
		{
			SetParent(&pParent);
		}

		void Action::SetParent(Attribute* pParent)
		{
			assert(pParent->Is(World::TypeIdClass()) || pParent->Is(Sector::TypeIdClass()) || pParent->Is(Entity::TypeIdClass()) || pParent->Is(ActionList::TypeIdClass()) );

			if (mParent != pParent)
			{
				pParent->Adopt(*this, Action::sActionKey);
				mParent = pParent;
			}
		}

		void Action::Populate()
		{
			Attribute::Populate();

			AppendPrescribedAttribute(sKeyAttribute).SetStorage(&mName, 1);
		}
	}
}