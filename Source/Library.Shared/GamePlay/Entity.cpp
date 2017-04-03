#include "pch.h"
#include "Entity.h"
#include "Sector.h"
#include "Parsers/WorldParseHelper.h"


namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(GamePlay::Entity)

		Entity::Entity() :
			Attribute(), mParent(nullptr), mName("")
		{
			Populate();
		}

		Entity::~Entity()
		{
		}

		std::string Entity::Name() const
		{
			return mName;
		}

		void Entity::SetName(const std::string& pName)
		{
			mName = pName;
		}

		Runtime::Datum& Entity::Actions()
		{
			return Append(Action::sActionKey);
		}

		Action& Entity::CreateAction(const std::string& pActionType, const std::string& pActionName)
		{
			Action* newAction = Generic::Factory<Action>::Create(pActionType);
			newAction->SetName(pActionName);

			newAction->SetParent(*this);

			return *newAction;
		}

		Sector& Entity::GetParentSector() const
		{
			return *mParent;
		}

		void Entity::SetParentSector(Sector& pSector)
		{
			if (mParent != &pSector)
			{
				pSector.Adopt(*this, Sector::sEntitiesKey);
				mParent = &pSector;
			}
		}

		void Entity::Update(WorldState& pWorldState)
		{
			Runtime::Datum& actionsList = Actions();

			for (uint32_t i = 0; i < actionsList.Size(); i++)
			{
				Action* action = reinterpret_cast<Action*>(actionsList.Get<Action*>(i));
				pWorldState.mCurrentAction = action;

				action->Update(pWorldState);
			}

			// reset
			pWorldState.mCurrentAction = nullptr;
		}

		void Entity::Populate()
		{
			Attribute::Populate();

			AppendPrescribedAttribute(Parsers::WorldParseHelper::sKeyAttribute).SetStorage(&mName, 1);
			AppendPrescribedAttribute(Action::sActionKey).SetType(Runtime::DatumType::TABLE);
		}
	}
}