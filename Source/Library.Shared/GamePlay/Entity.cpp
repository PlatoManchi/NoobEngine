#include "pch.h"
#include "Entity.h"
#include "Sector.h"
#include "Parsers/WorldParseHelper.h"


namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(GamePlay::Entity)

		const char* Entity::sEntitiesKey = "Entities";

		Entity::Entity() :
			Attribute(), mParent(nullptr), mName(""), mActionDatum(nullptr)
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
			return *mActionDatum;
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
				pSector.Adopt(*this, Entity::sEntitiesKey);
				mParent = &pSector;
			}
		}

		void Entity::Update(WorldState& pWorldState)
		{
			// update all actions in actions
			Runtime::Datum& actionsList = Actions();
			for (uint32_t i = 0; i < actionsList.Size(); i++)
			{
				Action* action = reinterpret_cast<Action*>(actionsList.Get<Scope*>(i));
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

			mActionDatum = &AppendPrescribedAttribute(Action::sActionKey);
			mActionDatum->SetType(Runtime::DatumType::TABLE);
		}
	}
}