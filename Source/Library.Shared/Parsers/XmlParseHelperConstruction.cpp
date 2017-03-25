#include "pch.h"
#include "XmlParseHelperConstruction.h"
#include "XmlSharedData.h"
#include "Utils/Utils.h"

namespace NoobEngine
{
	namespace Parsers
	{
		XmlParseHelperConstruction::XmlParseHelperConstruction()
		{ }

		XmlParseHelperConstruction::~XmlParseHelperConstruction()
		{ }

		void XmlParseHelperConstruction::Initialize(XmlParseMaster* pXmlParseMaster)
		{
			IXmlParseHelper::Initialize(pXmlParseMaster);

			if (mXmlParseMaster->GetSharedData())
			{
				if (mXmlParseMaster->GetSharedData()->Is(XmlSharedData::TypeIdClass()))
				{

				}
				else
				{
					throw std::exception("Invalid SharedData.");
				}
			}
		}

		bool XmlParseHelperConstruction::StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes)
		{
			pAttributes;
			XmlSharedData* sharedData = reinterpret_cast<XmlSharedData*>(mXmlParseMaster->GetSharedData());

			if (Utils::StrNCaseCmp(pElement, "construction"))
			{
				sharedData->mIsConstructionPhase = true;
			}

			
			if (sharedData->mIsConstructionPhase)
			{
				if (!(Utils::StrNCaseCmp(pElement, "int") ||
					Utils::StrNCaseCmp(pElement, "float") ||
					Utils::StrNCaseCmp(pElement, "string") ||
					Utils::StrNCaseCmp(pElement, "vec4") ||
					Utils::StrNCaseCmp(pElement, "mat4x4") ||
					Utils::StrNCaseCmp(pElement, "table") ||
					Utils::StrNCaseCmp(pElement, "construction") ))
				{
					if (sharedData->mCurrentPrototype != pElement)
					{
						sharedData->mCurrentPrototype = pElement;
						// create scope
						Runtime::Scope* prototypeScope = new Runtime::Scope();
						sharedData->mPrototypeScopes[pElement] = prototypeScope;
						sharedData->mCurrentRoot = prototypeScope;

						return true;
					}
				}
				else
				{
					// process data and put into prototype scope
					if (!Utils::StrNCaseCmp(sharedData->mCurrentTag, pElement))
					{
						sharedData->mArrayIndex = 0;
						sharedData->mCurrentTag = pElement;
					}

					// if the root is valid then process the data
					if (sharedData->mHasValidRoot)
					{
						// test if the grammar is proper
						if (pAttributes.ContainsKey("key") && pAttributes.ContainsKey("value"))
						{
							// process int element
							if (Utils::StrNCaseCmp(pElement, "int"))
							{
								if (pAttributes.ContainsKey("type") && Utils::StrNCaseCmp(pAttributes["type"], "array"))
								{
									sharedData->GetCurrentNode()[pAttributes["key"]].PushBack(stoi(pAttributes["value"]));
								}
								else
								{
									sharedData->mArrayIndex = 0;
									sharedData->GetCurrentNode()[pAttributes["key"]] = stoi(pAttributes["value"]);
								}

								// if successfully parsed
								return true;
							}

							// process float element
							else if (Utils::StrNCaseCmp(pElement, "float"))
							{
								if (pAttributes.ContainsKey("type") && Utils::StrNCaseCmp(pAttributes["type"], "array"))
								{
									sharedData->GetCurrentNode()[pAttributes["key"]].PushBack(stof(pAttributes["value"]));
								}
								else
								{
									sharedData->mArrayIndex = 0;
									sharedData->GetCurrentNode()[pAttributes["key"]] = stof(pAttributes["value"]);
								}


								// if successfully parsed
								return true;
							}

							// process string element
							else if (Utils::StrNCaseCmp(pElement, "string"))
							{
								if (pAttributes.ContainsKey("type") && Utils::StrNCaseCmp(pAttributes["type"], "array"))
								{
									std::string key = pAttributes["key"];
									std::string value = pAttributes["value"];
									sharedData->GetCurrentNode()[pAttributes["key"]].PushBack(pAttributes["value"]);
								}
								else
								{
									sharedData->mArrayIndex = 0;
									sharedData->GetCurrentNode()[pAttributes["key"]] = pAttributes["value"];
								}

								return true;
							}

							// process vector element
							else if (Utils::StrNCaseCmp(pElement, "vec4"))
							{
								sharedData->GetCurrentNode()[pAttributes["key"]].SetType(Runtime::DatumType::VECTOR_4);
								if (pAttributes.ContainsKey("type") && Utils::StrNCaseCmp(pAttributes["type"], "array"))
								{
									sharedData->GetCurrentNode()[pAttributes["key"]].SetFromString(pAttributes["value"], sharedData->mArrayIndex++);
								}
								else
								{
									sharedData->mArrayIndex = 0;
									sharedData->GetCurrentNode()[pAttributes["key"]].SetFromString(pAttributes["value"]);
								}


								return true;
							}

							// process matrix element
							else if (Utils::StrNCaseCmp(pElement, "mat4x4"))
							{
								sharedData->GetCurrentNode()[pAttributes["key"]].SetType(Runtime::DatumType::MATRIX_4x4);
								if (pAttributes.ContainsKey("type") && Utils::StrNCaseCmp(pAttributes["type"], "array"))
								{
									sharedData->GetCurrentNode()[pAttributes["key"]].SetFromString(pAttributes["value"], sharedData->mArrayIndex++);
								}
								else
								{
									sharedData->mArrayIndex = 0;
									sharedData->GetCurrentNode()[pAttributes["key"]].SetFromString(pAttributes["value"]);
								}
								return true;
							}
						}

						// table will have only name as key
						if (Utils::StrNCaseCmp(pElement, "table") && pAttributes.ContainsKey("key") && !pAttributes.ContainsKey("ref"))
						{
							Runtime::Scope& childTable = sharedData->GetCurrentNode().AppendScope(pAttributes["key"]);
							sharedData->mCurrentRoot = &childTable;

							return true;
						}
					}
				}
			}
			// its not construction phase
			else
			{
				// process table with ref
				if (Utils::StrNCaseCmp(pElement, "table") && pAttributes.ContainsKey("key") && pAttributes.ContainsKey("ref"))
				{
					std::string prototypeKey = pAttributes["ref"];
					if (sharedData->mPrototypeScopes.ContainsKey(prototypeKey))
					{
						sharedData->mIsPrototypeTable = true;

						Runtime::Scope* newScope = new Runtime::Scope(*sharedData->mPrototypeScopes[prototypeKey]);
						sharedData->GetCurrentNode().Adopt(*newScope, pAttributes["key"]);
						sharedData->mCurrentRoot = newScope;

						/*Runtime::Scope& childTable = sharedData->GetCurrentNode().AppendScope(pAttributes["key"]);
						childTable = *sharedData->mPrototypeScopes[prototypeKey];
						sharedData->mCurrentRoot = &childTable;*/

						return true;
					}
				}
			}
			return false;
		}

		bool XmlParseHelperConstruction::EndElementHandler(const std::string& pElement)
		{
			XmlSharedData* sharedData = reinterpret_cast<XmlSharedData*>(mXmlParseMaster->GetSharedData());

			if (Utils::StrNCaseCmp(pElement, "construction"))
			{
				sharedData->mIsConstructionPhase = false;
				sharedData->mCurrentRoot = sharedData->mRoot;
			}

			if (sharedData->mIsConstructionPhase)
			{
				return true;
			}
			else if(pElement == "table" && sharedData->mIsPrototypeTable)
			{
				sharedData->mCurrentRoot = sharedData->mCurrentRoot->GetParent();
				sharedData->mIsPrototypeTable = false;

				return true;
			}
			return false;
		}

		IXmlParseHelper * XmlParseHelperConstruction::Clone() const
		{
			return nullptr;
		}


	}
}