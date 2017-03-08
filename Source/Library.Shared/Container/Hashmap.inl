#include "Hashmap.h"

namespace NoobEngine
{
	namespace Container
	{
#pragma region Hashmap
		template <typename TKey, typename TValue, typename HashFunctor>
		Hashmap<TKey, TValue, HashFunctor>::Hashmap(uint32_t pHashmapBucketSize /* = 11 */) :
			mData(pHashmapBucketSize), mSize(0U)
		{
			if (pHashmapBucketSize == 0)
			{
				throw std::exception("Bucket size cannot be zero.");
			}

			SList<std::pair<TKey, TValue>> temp;
			for (uint32_t i = 0; i < pHashmapBucketSize; ++i)
			{
				mData.PushBack(temp);
			}
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		Hashmap<TKey, TValue, HashFunctor>::Hashmap(const Hashmap& pOther) :
			Hashmap(pOther.mData.Size())
		{
			operator=(pOther);
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		Hashmap<TKey, TValue, HashFunctor>::Hashmap(Hashmap<TKey, TValue, HashFunctor>&& pOther)
		{
			mData = move(pOther.mData);
			mSize = pOther.mSize;
			mHashFunctor = pOther.mHashFunctor;

			pOther.mSize = 0;
		}

		template <typename TKey, typename TValue, typename HashFunctor>
		Hashmap<TKey, TValue, HashFunctor>::~Hashmap()
		{
			Clear();
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::Find(const TKey& pKey) const
		{
			if (mData.Size() == 0)
			{
				return end();
			}

			uint32_t hashIndex = mHashFunctor(pKey) % mData.Size();
			const SList<std::pair<TKey, TValue>>& chainList = mData[hashIndex];

			for (SList<std::pair<TKey, TValue>>::Iterator listItr = chainList.begin(); listItr != chainList.end(); ++listItr)
			{
				if ((*listItr).first == pKey)
				{
					return Iterator(this, BucketType::Iterator(&mData, hashIndex), listItr);
				}
			}
			
			return end();
		}

		template <typename TKey, typename TValue, typename HashFunctor>
		typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::Insert(const TKey& pKey, const TValue& pValue)
		{
			std::pair<TKey, TValue> tmpPair(pKey, pValue);
			return Insert(tmpPair);
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::Insert(std::pair<TKey, TValue>& pKeyValuePair)
		{
			typename Hashmap<TKey, TValue, HashFunctor>::Iterator itr = Find(pKeyValuePair.first);
			if (itr != end())
			{
				return itr;
			}
			
			// if the key is not present in the hash map insert the key value pair
			uint32_t bucketIndex = mHashFunctor(pKeyValuePair.first) % mData.Size();
			typename SList<std::pair<TKey, TValue>>::Iterator elementItr = mData[bucketIndex].PushBack(pKeyValuePair);
 			typename BucketType::Iterator it = BucketType::Iterator(&mData, bucketIndex);

			mSize++;

			return Iterator(this, it, elementItr);
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		void Hashmap<TKey, TValue, HashFunctor>::Remove(const TKey & pKey)
		{
			typename Hashmap<TKey, TValue, HashFunctor>::Iterator itr = Find(pKey);
			if (itr != end())
			{
				(*itr.mHorizontalIterator).Remove((*itr));
				mSize--;
			}
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		void Hashmap<TKey, TValue, HashFunctor>::Clear()
		{
			// clearing all the buckets but keeping the vector as same
			for each (SList<std::pair<TKey, TValue>>& sList in mData)
			{
				sList.Clear();
			}
			
			mSize = 0;
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		uint32_t Hashmap<TKey, TValue, HashFunctor>::Size() const
		{
			return mSize;
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		bool Hashmap<TKey, TValue, HashFunctor>::ContainsKey(const TKey & pKey) const
		{
			for each (SList<std::pair<TKey, TValue>> list in mData)
			{
				for each (std::pair<TKey, TValue> pairData in list)
				{
					if (pairData.first == pKey)
					{
						return true;
					}
				}
			}
			return false;
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::begin() const
		{
			for (BucketType::Iterator itr = mData.begin() ; itr != mData.end() ; ++itr)
			{
				if ((*itr).Size() != 0)
				{
					return Iterator(this, itr, (*itr).begin());
				}
			}
			return end();
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		typename Hashmap<TKey, TValue, HashFunctor>::Iterator Hashmap<TKey, TValue, HashFunctor>::end() const
		{
			return Iterator(this, mData.end(), mData[mData.Size() - 1].end());
		}

		template<typename TKey, typename TValue, typename HashFunctor>
		Hashmap<TKey, TValue, HashFunctor>& Hashmap<TKey, TValue, HashFunctor>::operator=(Hashmap<TKey, TValue, HashFunctor>&& pOther)
		{
			Clear();

			mData = move(pOther.mData);
			mSize = pOther.mSize;
			//mHashFunctor = pOther.mHashFunctor;

			pOther.mSize = 0;

			return *this;
		}

		template <typename TKey, typename TValue, typename HashFunctor>
		TValue& Hashmap<TKey, TValue, HashFunctor>::operator[](const TKey& pKey)
		{
			std::pair<TKey, TValue> tmp;
			tmp.first = pKey;
			
			return (*Insert(tmp)).second;
		}

		template <typename TKey, typename TValue, typename HashFunctor>
		const TValue& Hashmap<TKey, TValue, HashFunctor>::operator[](const TKey& pKey) const
		{
			typename Hashmap<TKey, TValue, HashFunctor>::Iterator itr = Find(pKey);
			if (itr == end())
			{
				std::exception("Invalid key");
			}

			return (*itr).second;
		}
#pragma endregion

#pragma region Iterator
		template <typename TKey, typename TValue, typename HashFunctor>
		Hashmap<TKey, TValue, HashFunctor>::Iterator::Iterator(const Hashmap* pOwner, typename Vector<SList<std::pair<TKey, TValue>>>::Iterator pIteratorToBucket, typename SList<std::pair<TKey, TValue>>::Iterator pIteratorToPair) :
			mOwner(pOwner), mHorizontalIterator(pIteratorToBucket), mVerticalIterator(pIteratorToPair)
		{ }

		template <typename TKey, typename TValue, typename HashFunctor>
		Hashmap<TKey, TValue, HashFunctor>::Iterator::Iterator(const Iterator& pIterator) :
			mOwner(pIterator.mOwner), mHorizontalIterator(pIterator.mHorizontalIterator), mVerticalIterator(pIterator.mVerticalIterator)
		{ }

		template <typename TKey, typename TValue, typename HashFunctor>
		bool Hashmap<TKey, TValue, HashFunctor>::Iterator::operator==(const Iterator& pOther) const
		{
			return (mOwner == pOther.mOwner) &&
				(mHorizontalIterator == pOther.mHorizontalIterator) &&
				(mVerticalIterator == pOther.mVerticalIterator);
		}

		template <typename TKey, typename TValue, typename HashFunctor>
		bool Hashmap<TKey, TValue, HashFunctor>::Iterator::operator !=(const Iterator& pOther) const
		{
			return !(*this == pOther);
		}

		template <typename TKey, typename TValue, typename HashFunctor>
		std::pair<TKey, TValue>& Hashmap<TKey, TValue, HashFunctor>::Iterator::operator *()
		{
			if (!mOwner)
			{
				throw std::exception("Invalid iterator");
			}
			return (*mVerticalIterator);
		}

		template <typename TKey, typename TValue, typename HashFunctor>
		typename Hashmap<TKey, TValue, HashFunctor>::Iterator& Hashmap<TKey, TValue, HashFunctor>::Iterator::operator ++()
		{
			if (!mOwner)
			{
				throw std::exception("Invalid iterator");
			}

			if (*this == mOwner->end())
			{
				throw std::exception("Cannot increment end iterator.");
			}

			++mVerticalIterator;
			
			// if reached end of bucket
			if (mVerticalIterator == (*mHorizontalIterator).end())
			{
				// loop and check if there is any bucket left with elements in it
				while (mHorizontalIterator != mOwner->mData.end())
				{
					// go to next bucket
					++mHorizontalIterator;
					 
					if (mHorizontalIterator == mOwner->mData.end())
					{
						// no buckets left to search for next element
						break;
					}

					// first element in the next bucket
					mVerticalIterator = (*mHorizontalIterator).begin();
					if (mVerticalIterator != (*mHorizontalIterator).end())
					{
						// if the bucket is not empty then break loop
						break;
					}
				} // end of while
			}
			
			return *this;
		}
#pragma endregion

#pragma region DefaultHashFunctor
		// using additive hashing
		template <typename T>
		uint32_t DefaultHashFunction<T>::operator()(T pParam) const
		{
			const uint32_t len = sizeof(pParam);
			uint32_t hash = 0;

			unsigned char data[len];
			memcpy(data, static_cast<void*>(&pParam), len);

			uint32_t i;
			for (i = 0; i < len; i++)
			{
				hash += data[i];
			}

			return hash;
		}

		uint32_t DefaultHashFunction<std::string>::operator()(std::string pParam) const
		{
			size_t len = pParam.length();
			uint32_t hash = 0;

			uint32_t i;
			for (i = 0; i < len; i++)
			{
				hash += pParam[i];
			}

			return hash;
		}


		uint32_t DefaultHashFunction<char*>::operator()(const char* pParam) const
		{
			size_t len = strlen(pParam);
			uint32_t hash = 0;

			uint32_t i;
			for (i = 0; i < len; i++)
			{
				hash += pParam[i];
			}

			return hash;
		}

		uint32_t DefaultHashFunction<char*>::operator()(char* pParam) const
		{
			size_t len = strlen(pParam);
			uint32_t hash = 0;

			uint32_t i;
			for (i = 0; i < len; i++)
			{
				hash += pParam[i];
			}

			return hash;
		}
#pragma endregion
	}
}