#include "pch.h"
#include "Scope.h"

using namespace NoobEngine::Container;

namespace NoobEngine
{
	namespace Runtime
	{
		RTTI_DEFINITIONS(Scope)

		Scope::Scope(uint32_t pSize) : mParent(nullptr), mData(Hashmap<std::string, Datum>(pSize))
		{}

		Scope::Scope(const Scope& pOther) : mParent(pOther.mParent), mData(pOther.mData), mDataIndexing(pOther.mDataIndexing)
		{}

		Scope::~Scope()
		{
			Clear();
			RTTI::~RTTI();
		}

		Datum* Scope::Find(const std::string& pKey) const
		{
			Hashmap<std::string, Datum>::Iterator itr = mData.Find(pKey);
			if(itr != mData.end())
			{
				return &(*itr).second;
			}
			return nullptr;
		}

		Datum* Scope::Search(const std::string& pKey, Scope** pScope) const
		{
			//  initializing the output param
			*pScope = nullptr;

			Datum* findInScope = Find(pKey);
			if(findInScope)
			{
				*pScope = const_cast<Scope*>(this);
			}
			else
			{
				if(mParent)
				{
					// if scope has parent, search for key up the hierarchy
					findInScope = mParent->Search(pKey, pScope);
				}
			}

			return findInScope;
		}

		Datum& Scope::Append(const std::string& pKey)
		{
			Datum* findInScope = Find(pKey);
			if(findInScope)
			{
				return *findInScope;
			}

			// insert a default datum of unassigned type table and push the std::pair into vector for indexing
			Hashmap<std::string, Datum>::Iterator itr = mData.Insert(pKey, Datum());
			mDataIndexing.PushBack(&(*itr));

			return (*itr).second;
		}

		Scope& Scope::AppendScope(const std::string& pKey)
		{
			Datum findInScope = Append(pKey);
			
			Scope* newScope = new Scope();
			findInScope.PushBack(newScope);

			return  *newScope;
		}

		void Scope::Adopt(Scope& pChildToAdopt, const std::string& pKey)
		{
			pChildToAdopt.Orphan();
			pChildToAdopt.mParent = this;

			operator[](pKey).PushBack(&pChildToAdopt);
		}

		Scope* Scope::GetParent() const
		{
			return mParent;
		}

		std::string Scope::FindName(const Scope& pScope)
		{
			if(this != pScope.mParent)
			{
				// early out
				return "";
			}

			for(const std::pair<std::string, Datum>* element : mDataIndexing)
			{
				if(element->second.Type() == DatumType::TABLE)
				{
					// loop thorough all the scope pointers that datum contains
					for(uint32_t i = 0 ; i < element->second.Size() ; i++)
					{
						Scope* tmp = element->second.Get<Scope*>(i);
						if(*tmp == pScope)
						{
							return element->first;
						}
					}
				}
			}
			
			return "";
		}

		bool Scope::Equals(const RTTI* pOther) const
		{
			if(this == pOther)
			{
				return true;
			}

			if(!pOther)
			{
				return false;
			}

			Scope* scope = pOther->As<Scope>();

			if(scope)
			{
				return operator==(*scope);
			}
			return false;			
		}

		std::string Scope::ToString() const
		{
			return "Scope";
		}

		Scope& Scope::operator=(const Scope& pOther)
		{
			if(this != &pOther)
			{
				Clear();
				for (std::pair<std::string, Datum>& element : pOther.mData)
				{
					if(element.second.Type() != DatumType::TABLE)
					{
						Append(element.first) = element.second;
					}
					else
					{
						for(uint32_t i = 0 ; i < element.second.Size() ; ++i)
						{
							Scope* tmpScope = new Scope(*element.second.Get<Scope*>(i));
							tmpScope->mParent = this;
							Append(element.first).PushBack(tmpScope);
						}
					}
				}
			}

			return *this;
		}

		Datum& Scope::operator[](const std::string& pKey)
		{
			return Append(pKey);
		}

		Datum& Scope::operator[](uint32_t pIndex) const
		{
			if(pIndex >= mDataIndexing.Size())
			{
				throw std::exception("Index out of bounds.");
			}

			return mDataIndexing[pIndex]->second;
		}

		bool Scope::operator==(const Scope& pOther) const
		{
			if(this == &pOther)
			{
				return true;
			}

			if(mDataIndexing.Size() != pOther.mDataIndexing.Size())
			{
				return false;
			}

			for(uint32_t i = 0 ; i < mDataIndexing.Size() ; ++i)
			{
				if(mDataIndexing[i] != pOther.mDataIndexing[i])
				{
					return false;
				}
			}

			return true;
		}

		bool Scope::operator!=(const Scope& pOther) const
		{
			return !(operator==(pOther));
		}

		void Scope::Clear()
		{
			for (std::pair<std::string, Datum>* element : mDataIndexing)
			{
				if(element->second.Type() == DatumType::TABLE)
				{
					uint32_t tableSize = element->second.Size();
					for(uint32_t i = 0 ; i < tableSize ; ++i)
					{
						delete (element->second.Get<Scope*>(i));
					}
				}
				element->second.~Datum();
			}
		}

		void Scope::Orphan()
		{
			if(mParent)
			{
				// if scope has parent remove all this scope's footprints from parent
				std::string name = FindName(*this);

				for(std::pair<std::string, Datum> *element : mParent->mDataIndexing)
				{
					if(element->first == name)
					{
						// found the datum with name
						Datum& parentDatum = element->second;
						
						for(uint32_t i =0 ; i < parentDatum.Size() ; ++i)
						{
							if(this == parentDatum.Get<Scope*>(i))
							{
								// found the scope in parent datum
								parentDatum.RemoveSafeAt(i);
								mParent = nullptr;
								return;
							}
						}
					}
				}
			}
		}


	}
}
