#include "pch.h"
#include "XmlParseHelperTable.h"
#include "Utils/Utils.h"

namespace NoobEngine
{
	namespace Parsers
	{
#pragma region XmlParseHelperTable::XmlTableParser
		XmlParseHelperTable::XmlTableParser::XmlTableParser() :
			XmlParseMaster::SharedData(), mHasValidRoot(false), mRoot(nullptr), mCurrentRoot(nullptr), mCurrentTag(""), mIsConstructionPhase(false), mArrayIndex(0), mIsPrototypeTable(false)
		{
		}

		XmlParseHelperTable::XmlTableParser::~XmlTableParser()
		{
		}

		XmlParseMaster::SharedData* XmlParseHelperTable::XmlTableParser::Clone() const
		{
			XmlParseHelperTable::XmlTableParser* clonedData = new XmlParseHelperTable::XmlTableParser();

			// creating copy of all the internal data
			if (mRoot)
			{
				clonedData->mRoot = new Runtime::Scope(*mRoot);
				clonedData->mCurrentRoot = clonedData->mRoot;
			}

			return clonedData;
		}
		Runtime::Scope& XmlParseHelperTable::XmlTableParser::GetRootNode() const
		{
			return *mRoot;
		}
		Runtime::Scope & XmlParseHelperTable::XmlTableParser::GetCurrentNode() const
		{
			return *mCurrentRoot;
		}
#pragma endregion

		XmlParseHelperTable::XmlParseHelperTable()
		{
		}

		XmlParseHelperTable::~XmlParseHelperTable()
		{
		}

		void XmlParseHelperTable::Initialize(XmlParseMaster* pXmlParseMaster)
		{
			IXmlParseHelper::Initialize(pXmlParseMaster);

			if (mXmlParseMaster->GetSharedData())
			{
				if (mXmlParseMaster->GetSharedData()->Is(XmlTableParser::TypeIdClass()))
				{

				}
				else
				{
					throw std::exception("Invalid SharedData.");
				}
			}
		}

		bool XmlParseHelperTable::StartElementHandler(const std::string& pElement, const NoobEngine::Container::Hashmap<std::string, std::string>& pAttributes)
		{
			XmlTableParser* sharedData = reinterpret_cast<XmlTableParser*>(mXmlParseMaster->GetSharedData());

			if (Utils::StrNCaseCmp(pElement, "construction"))
			{
				sharedData->mIsConstructionPhase = true;
			}

			// checking if the first element is root
			if (mXmlParseMaster->GetSharedData()->Depth() == 1)
			{
				mHasValidRoot = Utils::StrNCaseCmp(pElement.c_str(), "root");
				sharedData->mHasValidRoot = mHasValidRoot;
				// create the scope only if the root is valid
				if (mHasValidRoot && !sharedData->mRoot)
				{
					sharedData->mRoot = new Runtime::Scope();
					sharedData->mCurrentRoot = sharedData->mRoot;
				}

				// this helper will process the xml only if the first element is names as 'root'
				return mHasValidRoot;
			}

			// if its construction phase
			if (sharedData->mIsConstructionPhase)
			{
				return false;
			}

			if (!Utils::StrNCaseCmp(sharedData->mCurrentTag, pElement))
			{
				sharedData->mArrayIndex = 0;
				sharedData->mCurrentTag = pElement;
			}

			// if the root is valid then process the data
			if (mHasValidRoot && !sharedData->mIsPrototypeTable)
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
				if (Utils::StrNCaseCmp(pElement, "table") && pAttributes.ContainsKey("key"))
				{
					sharedData->mIsPrototypeTable = pAttributes.ContainsKey("ref");
					if (!sharedData->mIsPrototypeTable)
					{
						Runtime::Scope& childTable = sharedData->GetCurrentNode().AppendScope(pAttributes["key"]);
						sharedData->mCurrentRoot = &childTable;
						
						return true;
					}
					
					return false;
				}
			}

			return false;
		}

		bool XmlParseHelperTable::EndElementHandler(const std::string& pElement)
		{
			XmlTableParser* sharedData = reinterpret_cast<XmlTableParser*>(mXmlParseMaster->GetSharedData());

			if (Utils::StrNCaseCmp(pElement, "construction"))
			{
				sharedData->mIsConstructionPhase = false;
			}

			// if its construction phase
			if (sharedData->mIsConstructionPhase)
			{
				return false;
			}

			if (pElement == "table" && !sharedData->mIsPrototypeTable)
			{
				sharedData->mCurrentRoot = sharedData->mCurrentRoot->GetParent();

				return true;
			}

			return false;
		}

		IXmlParseHelper* XmlParseHelperTable::Clone() const
		{
			XmlParseHelperTable* cloneHelper = new XmlParseHelperTable();
			return cloneHelper;
		}

	}
}