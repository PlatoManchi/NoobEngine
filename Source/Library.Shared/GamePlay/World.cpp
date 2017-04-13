#include "pch.h"
#include "World.h"
#include "Sector.h"
#include "Parsers/WorldParseHelper.h"
#include "Action.h"
#include "Generic/Factory.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(GamePlay::World)

		World::World() :
			Attribute(), mName("")
		{
			Populate();
		}

		World::~World()
		{
		}

		std::string World::Name() const
		{
			return mName;
		}

		void World::SetName(const std::string& pName)
		{
			mName = pName;
		}

		Runtime::Datum& World::Sectors()
		{
			return Append(Sector::sSectorsKey);
		}

		Runtime::Datum& World::Actions()
		{
			return Append(Action::sActionKey);
		}

		Sector& World::CreateSector(const std::string& pSectorName)
		{
			Sector* newSector = new Sector();
			newSector->SetName(pSectorName);

			newSector->SetParentWorld(*this);

			return *newSector;
		}

		Action& World::CreateAction(const std::string& pActionType, const std::string& pActionName)
		{
			Action* newAction = Generic::Factory<Action>::Create(pActionType);
			newAction->SetName(pActionName);

			newAction->SetParent(*this);

			return *newAction;
		}

		void World::Update(WorldState& pWorldState)
		{
			pWorldState.mCurrentWorld = this;
			pWorldState.mCurrentSector = nullptr;
			pWorldState.mCurrentEntity = nullptr;
			pWorldState.mCurrentAction = nullptr;

			pWorldState.Update();

			// update all actions in world
			Runtime::Datum& actionsList = Actions();
			for (uint32_t i = 0U; i < actionsList.Size(); ++i)
			{
				Action* action = reinterpret_cast<Action*>(actionsList.Get<Scope*>(i));
				pWorldState.mCurrentAction = action;

				action->Update(pWorldState);
			}

			// reset
			pWorldState.mCurrentAction = nullptr;

			// update all sectors in world
			Runtime::Datum& sectorsList = Sectors();
			for (uint32_t i = 0; i < sectorsList.Size(); ++i)
			{
				Sector* sector = reinterpret_cast<Sector*>(sectorsList.Get<Scope*>(i));
				pWorldState.mCurrentSector = sector;

				sector->Update(pWorldState);
			}

			// reset
			pWorldState.mCurrentSector = nullptr;

			// doing garbage collection
			for (Action* action : mGarbageQueue)
			{
				action->Orphan();
				delete action;
			}
			// clearing garbage list
			mGarbageQueue.Clear();
		}

		void World::Populate()
		{
			Attribute::Populate();

			AppendPrescribedAttribute(Parsers::WorldParseHelper::sKeyAttribute).SetStorage(&mName, 1);
			AppendPrescribedAttribute(Sector::sSectorsKey).SetType(Runtime::DatumType::TABLE);
			AppendPrescribedAttribute(Action::sActionKey).SetType(Runtime::DatumType::TABLE);
		}

		void World::DestroyAction(Action& pActionToDestroy)
		{
			mGarbageQueue.PushBack(&pActionToDestroy);
		}

		Runtime::Datum* World::ResolveDatum(std::string pDatumPath)
		{
			char* tokens;
			tokens = strtok(const_cast<char*>(pDatumPath.c_str()), ".");
			Runtime::Scope* currentScope = this;
			Runtime::Datum* result = nullptr;
			bool isCurentLevelFound = true;

			while (tokens != nullptr && isCurentLevelFound)
			{
				isCurentLevelFound = false;
				if (currentScope)
				{
					for (std::pair<std::string, Runtime::Datum>& element : *currentScope)
					{
						// search through every datum int he scope
						Runtime::Datum& searchingDatum = element.second;
						if (searchingDatum.Type() == Runtime::DatumType::TABLE)
						{
							for (uint32_t i = 0; i < searchingDatum.Size(); ++i)
							{
								// check every table in the datum
								Runtime::Scope* scope = searchingDatum.Get<Scope*>(i);
								if (scope->Is(Attribute::TypeIdClass()))
								{
									Runtime::Attribute* attrib = reinterpret_cast<Runtime::Attribute*>(scope);

									if (attrib->IsAttribute(Parsers::WorldParseHelper::sKeyAttribute))
									{
										if ((*attrib)[Parsers::WorldParseHelper::sKeyAttribute].Get<std::string>() == tokens)
										{
											currentScope = scope;
											isCurentLevelFound = true;
											result = &searchingDatum;
											break;
										}
									}

								}
							}
						}
						else
						{
							// check if this datum is the one wanted
							if (element.first == tokens)
							{
								isCurentLevelFound = true;
								result = &searchingDatum;
								break;
							}
						}

						if (isCurentLevelFound) break;
					}
				}

				// getting next token
				tokens = strtok(nullptr, ".");
			}

			return isCurentLevelFound ? result : nullptr;
		}
	}
}