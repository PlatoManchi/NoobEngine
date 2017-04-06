#include "pch.h"
#include "WorldParseHelper.h"
#include "WorldSharedData.h"
#include "GamePlay/World.h"
#include "GamePlay/Sector.h"
#include "Utils/Utils.h"

namespace NoobEngine
{
	namespace Parsers
	{
		const std::string WorldParseHelper::sIntTag = "int";
		const std::string WorldParseHelper::sFloatTag = "float";
		const std::string WorldParseHelper::sStringTag = "string";
		const std::string WorldParseHelper::sVec4Tag = "vec4";
		const std::string WorldParseHelper::sMat4x4Tag = "mat4x4";
		const std::string WorldParseHelper::sTableTag = "table";
		const std::string WorldParseHelper::sKeyAttribute = "key";
		const std::string WorldParseHelper::sValueAttribute = "value";

		const std::string WorldParseHelper::sWorldTag = "world";
		const std::string WorldParseHelper::sSectorTag = "sector";
		const std::string WorldParseHelper::sEntityTag = "entity";
		
		const std::string WorldParseHelper::sEntityClassAttribute = "class";

		const std::string WorldParseHelper::sWorldsKey = "worlds";

		WorldParseHelper::WorldParseHelper() :
			IXmlParseHelper(), mHasValidRoot(false), mIsValidSector(false), mIsValidEntity(false), mIsTable(false)
		{
		}

		WorldParseHelper::~WorldParseHelper()
		{
		}

		void WorldParseHelper::Initialize(XmlParseMaster& pXmlParseMaster)
		{
			IXmlParseHelper::Initialize(pXmlParseMaster);

			if (mXmlParseMaster->GetSharedData())
			{
				if (!mXmlParseMaster->GetSharedData()->Is(WorldSharedData::TypeIdClass()))
				{
					throw std::exception("Invalid SharedData.");
				}
			}
		}

		bool WorldParseHelper::StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes)
		{
			WorldSharedData* sharedData = reinterpret_cast<WorldSharedData*>(mXmlParseMaster->GetSharedData());

			if (Utils::StrNCaseCmp(pElement, "construction"))
			{
				sharedData->mIsConstructionPhase = true;
			}

			// checking if the first element is world
			if (mXmlParseMaster->GetSharedData()->Depth() == 1)
			{
				mHasValidRoot = Utils::StrNCaseCmp(pElement.c_str(), sWorldTag);
				sharedData->mHasValidRoot = mHasValidRoot;
				// create the scope only if the root is valid
				if (mHasValidRoot && !sharedData->mRoot)
				{
					// create new world if the root is valid
					
					GamePlay::World* world = new GamePlay::World();
					sharedData->mRoot = world;
					sharedData->mRoot->Adopt(*world, sWorldsKey);
					sharedData->mCurrentRoot = world;

					if (pAttributes.ContainsKey(sKeyAttribute))
					{
						world->SetName(pAttributes[sKeyAttribute]);
					}
				}

				// this helper will process the xml only if the first element is names as 'root'
				return mHasValidRoot;
			}
			if (mHasValidRoot)
			{
				// if its construction phase
				// construction is handled by 
				if (sharedData->mIsConstructionPhase)
				{
					return false;
				}

				// for processing array
				if (!Utils::StrNCaseCmp(sharedData->mCurrentTag, pElement))
				{
					sharedData->mArrayIndex = 0;
					sharedData->mCurrentTag = pElement;
				}

				if (Utils::StrNCaseCmp(pElement, sSectorTag) && pAttributes.ContainsKey(sKeyAttribute))
				{
					mIsValidSector = true;
					GamePlay::World* rootWorld = reinterpret_cast<GamePlay::World*>(sharedData->mRoot);
					
					sharedData->mCurrentRoot = reinterpret_cast<Runtime::Scope*>(&rootWorld->CreateSector(pAttributes[sKeyAttribute]));

					return true;
				}

				if (mIsValidSector)
				{
					// process entity and other data
					if (Utils::StrNCaseCmp(pElement, sEntityTag) && pAttributes.ContainsKey(sKeyAttribute))
					{
						mIsValidEntity = true;

						GamePlay::Sector* currentSector = reinterpret_cast<GamePlay::Sector*>(sharedData->mCurrentRoot);
						std::string entityClass = "Entity"; // default entity class
						if (pAttributes.ContainsKey(sEntityClassAttribute))
						{
							entityClass = pAttributes[sEntityClassAttribute];
						}

						sharedData->mCurrentRoot = reinterpret_cast<Runtime::Scope*>(&currentSector->CreateEntity(entityClass, pAttributes[sKeyAttribute]));

						return true;
					}
				}
			}

			if (mHasValidRoot || mIsValidEntity || mIsValidSector)
			{
				// test if the grammar is proper
				if (pAttributes.ContainsKey(sKeyAttribute) && pAttributes.ContainsKey(sValueAttribute))
				{
					// process int element
					if (Utils::StrNCaseCmp(pElement, sIntTag))
					{
						if (pAttributes.ContainsKey("type") && Utils::StrNCaseCmp(pAttributes["type"], "array"))
						{
							sharedData->GetCurrentNode()[pAttributes[sKeyAttribute]].PushBack(stoi(pAttributes[sValueAttribute]));
						}
						else
						{
							sharedData->mArrayIndex = 0;
							sharedData->GetCurrentNode()[pAttributes[sKeyAttribute]] = stoi(pAttributes[sValueAttribute]);
						}

						// if successfully parsed
						return true;
					}

					// process float element
					else if (Utils::StrNCaseCmp(pElement, sFloatTag))
					{
						if (pAttributes.ContainsKey("type") && Utils::StrNCaseCmp(pAttributes["type"], "array"))
						{
							sharedData->GetCurrentNode()[pAttributes[sKeyAttribute]].PushBack(stof(pAttributes[sValueAttribute]));
						}
						else
						{
							sharedData->mArrayIndex = 0;
							sharedData->GetCurrentNode()[pAttributes[sKeyAttribute]] = stof(pAttributes[sValueAttribute]);
						}


						// if successfully parsed
						return true;
					}

					// process string element
					else if (Utils::StrNCaseCmp(pElement, sStringTag))
					{
						if (pAttributes.ContainsKey("type") && Utils::StrNCaseCmp(pAttributes["type"], "array"))
						{
							sharedData->GetCurrentNode()[pAttributes[sKeyAttribute]].PushBack(pAttributes[sValueAttribute]);
						}
						else
						{
							sharedData->mArrayIndex = 0;
							sharedData->GetCurrentNode()[pAttributes[sKeyAttribute]] = pAttributes[sValueAttribute];
						}

						return true;
					}

					// process vector element
					else if (Utils::StrNCaseCmp(pElement, sVec4Tag))
					{
						sharedData->GetCurrentNode()[pAttributes["key"]].SetType(Runtime::DatumType::VECTOR_4);
						if (pAttributes.ContainsKey("type") && Utils::StrNCaseCmp(pAttributes["type"], "array"))
						{
							sharedData->GetCurrentNode()[pAttributes[sKeyAttribute]].SetFromString(pAttributes[sValueAttribute], sharedData->mArrayIndex++);
						}
						else
						{
							sharedData->mArrayIndex = 0;
							sharedData->GetCurrentNode()[pAttributes[sKeyAttribute]].SetFromString(pAttributes[sValueAttribute]);
						}


						return true;
					}

					// process matrix element
					else if (Utils::StrNCaseCmp(pElement, sMat4x4Tag))
					{
						sharedData->GetCurrentNode()[pAttributes["key"]].SetType(Runtime::DatumType::MATRIX_4x4);
						if (pAttributes.ContainsKey("type") && Utils::StrNCaseCmp(pAttributes["type"], "array"))
						{
							sharedData->GetCurrentNode()[pAttributes[sKeyAttribute]].SetFromString(pAttributes[sValueAttribute], sharedData->mArrayIndex++);
						}
						else
						{
							sharedData->mArrayIndex = 0;
							sharedData->GetCurrentNode()[pAttributes[sKeyAttribute]].SetFromString(pAttributes[sValueAttribute]);
						}
						return true;
					}
				} // end of grammar check

				  // table will have only name as key
				if (Utils::StrNCaseCmp(pElement, sTableTag) && pAttributes.ContainsKey(sKeyAttribute))
				{
					sharedData->mIsPrototypeTable = pAttributes.ContainsKey("ref");
					if (!sharedData->mIsPrototypeTable)
					{
						Runtime::Scope& childTable = sharedData->GetCurrentNode().AppendScope(pAttributes[sKeyAttribute]);
						sharedData->mCurrentRoot = &childTable;

						return true;
					}

					return false;
				} // end of grammar check for table

			}
			
			return false;
		}


		bool WorldParseHelper::EndElementHandler(const std::string& pElement)
		{
			WorldSharedData* sharedData = reinterpret_cast<WorldSharedData*>(mXmlParseMaster->GetSharedData());

			if (Utils::StrNCaseCmp(pElement, "construction"))
			{
				sharedData->mIsConstructionPhase = false;
				return true;
			}

			// if its construction phase
			if (sharedData->mIsConstructionPhase)
			{
				return false;
			}

			if (!sharedData->mIsPrototypeTable)
			{
				if (mIsValidSector && Utils::StrNCaseCmp(pElement, sSectorTag))
				{
					mIsValidSector = false;
					sharedData->mCurrentRoot = sharedData->mCurrentRoot->GetParent();

					return true;
				}

				if (mIsValidEntity && Utils::StrNCaseCmp(pElement, sEntityTag))
				{
					mIsValidEntity = false;
					sharedData->mCurrentRoot = sharedData->mCurrentRoot->GetParent();

					return true;
				}

				if (mIsTable && Utils::StrNCaseCmp(pElement, sTableTag))
				{
					mIsTable = false;
					sharedData->mCurrentRoot = sharedData->mCurrentRoot->GetParent();

					return true;
				}

				if ((mIsValidEntity || mIsValidSector)&&
					(Utils::StrNCaseCmp(pElement, sIntTag) ||
						Utils::StrNCaseCmp(pElement, sFloatTag) ||
						Utils::StrNCaseCmp(pElement, sStringTag) ||
						Utils::StrNCaseCmp(pElement, sVec4Tag) ||
						Utils::StrNCaseCmp(pElement, sMat4x4Tag))
					)
				{
					// if its entity and any of primitive tag
					return true;
				}
			}

			return false;
		}


		IXmlParseHelper* WorldParseHelper::Clone() const
		{
			return nullptr;
		}
	}
}