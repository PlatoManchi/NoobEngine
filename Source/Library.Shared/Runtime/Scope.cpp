#include "pch.h"
#include "Scope.h"

using namespace NoobEngine::Container;

namespace NoobEngine
{
	namespace Runtime
	{
		RTTI_DEFINITIONS(Scope)

		Scope::Scope(uint32_t pSize) : mParent(nullptr), mData(pSize), mDataIndexing(pSize)
		{}

		Scope::Scope(const Scope& pOther) : Scope(pOther.mDataIndexing.Capacity())
		{
			operator=(pOther);
		}

		Scope::Scope(Scope&& pOther) : 
			RTTI(std::move(pOther))
		{
			mParent = pOther.mParent;
			mData = std::move(pOther.mData);
			mDataIndexing = std::move(pOther.mDataIndexing);

			// update the parent of all child scopes to this
			for (std::pair<std::string, Datum>& element : mData)
			{
				if (element.second.Type() == DatumType::TABLE)
				{
					for (uint32_t i = 0u; i < element.second.Size(); ++i)
					{
						element.second.Get<Scope*>(i)->mParent = this;
					}
				}
			}

			// if this scope has a parent then update the pointer to point to this scope instead of pOther
			if (mParent)
			{
				Datum* foundDatum;
				int32_t foundAt;
				mParent->FindName(pOther, &foundDatum, &foundAt);

				if (foundDatum)
				{
					foundDatum->Set(this, foundAt);
				}
			}

			pOther.mParent = nullptr;
		}

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
			Datum tmpDatum = Datum();
			Hashmap<std::string, Datum>::Iterator itr = mData.Insert(pKey, tmpDatum);
			mDataIndexing.PushBack(&(*itr));

			return (*itr).second;
		}

		Scope& Scope::AppendScope(const std::string& pKey)
		{
			Datum& findInScope = Append(pKey);
			
			Scope* newScope = new Scope;
			newScope->mParent = this;

			findInScope.PushBack(newScope);

			return  *newScope;
		}

		void Scope::Adopt(Scope& pChildToAdopt, const std::string& pKey)
		{
			if(this == &pChildToAdopt)
			{
				// if trying to adopt self
				return;
			}

			pChildToAdopt.Orphan();
			pChildToAdopt.mParent = this;

			operator[](pKey).PushBack(&pChildToAdopt);
		}

		Scope* Scope::GetParent() const
		{
			return mParent;
		}

		std::string Scope::FindName(const Scope& pScope, Datum** pFoundInDatum, int32_t* pFoundAt)
		{
			if (pFoundAt)
			{
				*pFoundAt = -1;
			}

			if (pFoundInDatum)
			{
				*pFoundInDatum = nullptr;
			}

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
							if (pFoundInDatum)
							{
								*pFoundInDatum = const_cast<Datum*>(&element->second);
							}
							if (pFoundAt)
							{
								*pFoundAt = i;
							}
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
				for (std::pair<std::string, Datum>* element : pOther.mDataIndexing)
				{
					if(element->second.Type() != DatumType::TABLE)
					{
						Append(element->first) = element->second;
					}
					else
					{
						for(uint32_t i = 0 ; i < element->second.Size() ; ++i)
						{
							Scope* tmpScope = new Scope(*element->second.Get<Scope*>(i));
							tmpScope->mParent = this;
							Append(element->first).PushBack(tmpScope);
						}
					}
				}
			}

			return *this;
		}

		Scope& Scope::operator=(Scope&& pOther)
		{
			if (this != &pOther)
			{
				Clear();

				mParent = pOther.mParent;
				mData = std::move(pOther.mData);
				mDataIndexing = std::move(pOther.mDataIndexing);

				// update the parent of all child scopes to this
				for (std::pair<std::string, Datum>& element : mData)
				{
					if (element.second.Type() == DatumType::TABLE)
					{
						for (uint32_t i = 0; i < element.second.Size(); ++i)
						{
							element.second.Get<Scope*>(i)->mParent = this;
						}
					}
				}

				// if this scope has a parent then update the pointer to point to this scope instead of pOther
				if (mParent)
				{
					Datum* foundDatum;
					int32_t foundAt;
					mParent->FindName(pOther, &foundDatum, &foundAt);

					if (foundDatum)
					{
						foundDatum->Set(this, foundAt);
					}
				}

				pOther.mParent = nullptr;
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
				std::pair<std::string, Datum>* pair1 = mDataIndexing[i];
				std::pair<std::string, Datum>* pair2 = pOther.mDataIndexing[i];

				if(!(pair1->first == pair2->first &&
					pair1->second == pair2->second))
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
			}
		}

		void Scope::Orphan()
		{
			if(mParent)
			{
				// if scope has parent remove all this scope's footprints from parent
				std::string name = mParent->FindName(*this);

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
