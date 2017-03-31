
#include "SList.h"

using namespace std;

namespace NoobEngine
{
	namespace Container
	{

		template <typename T>
		SList<T>::SList() :
			mFrontNode(nullptr), mBackNode(nullptr), mSize(0)
		{}

		template <typename T>
		SList<T>::SList(const SList& pList) :
			mFrontNode(nullptr), mBackNode(nullptr), mSize(0)
		{
			for each(T element in pList)
			{
				PushBack(element);
			}
		}

		template<typename T>
		SList<T>::SList(SList&& pList) :
			mFrontNode(pList.mFrontNode), mBackNode(pList.mBackNode), mSize(pList.mSize)
		{
			pList.mFrontNode = nullptr;
			pList.mBackNode = nullptr;
			pList.mSize = 0;
		}

		template <typename T>
		SList<T>::~SList()
		{
			Clear();
		}

		template <typename T>
		SList<T>& SList<T>::operator=(const SList& pList)
		{
			// making sure that assignment operator is not called on itself
			if (this != &pList)
			{
				// clear all the previous elements held by the current list
				Clear();

				for each(const T& element in pList)
				{
					PushBack(element);
				}
				
			}

			return *this;
		}

		template<typename T>
		SList<T>& SList<T>::operator=(SList&& pList)
		{
			if (this != &pList)
			{
				Clear();

				mFrontNode = pList.mFrontNode;
				mBackNode = pList.mBackNode;
				mSize = pList.mSize;

				pList.mFrontNode = nullptr;
				pList.mBackNode = nullptr;
				pList.mSize = 0;
			}
			
			return *this;
		}

		template <typename T>
		typename SList<T>::Iterator SList<T>::PushFront(const T& pData)
		{
			Node* node = new Node(pData, mFrontNode);

			if (!mFrontNode)
			{
				// empty list
				mBackNode = node;
			}

			mFrontNode = node;
			mSize++;

			return begin();
		}

		template <typename T>
		typename SList<T>::Iterator SList<T>::PushBack(const T& pData)
		{
			Node* node = new Node(pData, nullptr);
			node->mData = pData;

			if (mFrontNode)
			{
				mBackNode->mNextNode = node;
			}
			else
			{
				// empty list
				mFrontNode = node;
			}

			mBackNode = node;
			mSize++;

			return Iterator(this, node);
		}

		template <typename T>
		T SList<T>::PopFront()
		{
			if (mSize == 0)
			{
				throw exception("Calling Pop on empty list.");
			}

			// saving reference of front node and the data in temp variables
			Node* frontNode = mFrontNode;
			T data = mFrontNode->mData;

			mFrontNode = mFrontNode->mNextNode;
			delete(frontNode);

			--mSize;

			return data;
		}

		template <typename T>
		T& SList<T>::Front()
		{
			if (mSize == 0)
			{
				throw exception("Calling Front on empty list.");
			}

			return mFrontNode->mData;
		}

		template <typename T>
		const T& SList<T>::Front() const
		{
			if (mSize == 0)
			{
				throw exception("Calling Front on empty list.");
			}

			return mFrontNode->mData;
		}

		template <typename T>
		T& SList<T>::Back()
		{
			if (mSize == 0)
			{
				throw exception("Calling Back on empty list.");
			}

			return mBackNode->mData;
		}

		template <typename T>
		const T& SList<T>::Back() const
		{
			if (mSize == 0)
			{
				throw exception("Calling Back on empty list.");
			}

			return mBackNode->mData;
		}

		template <typename T>
		void SList<T>::Clear()
		{
			while (mSize != 0)
			{
				PopFront();
			}
		}

		template <typename T>
		uint32_t SList<T>::Size() const
		{
			return mSize;
		}

		template <typename T>
		bool SList<T>::IsEmpty() const
		{
			return (mFrontNode == nullptr);
		}

		template <typename T>
		typename SList<T>::Iterator SList<T>::Find(const T& pObject) const
		{
			for (SList<T>::Iterator itr = begin(); itr != end(); ++itr)
			{
				if (pObject == *itr)
				{
					return itr;
				}
			}

			// if the object is not found
			return end();
		}

		template <typename T>
		void SList<T>::Remove(const T& pObject)
		{
			typename SList<T>::Iterator prevNodeIterator = begin();
			for (SList<T>::Iterator itr = begin(); itr != end(); ++itr)
			{
				if (pObject == *itr)
				{
					if (itr == this->begin())
					{
						mFrontNode = itr.mNode->mNextNode;
					}
					else
					{
						prevNodeIterator.mNode->mNextNode = itr.mNode->mNextNode;
					}
					mSize--;
					delete(itr.mNode);
					return;
				}

				prevNodeIterator = itr;
			}
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::InsertAfter(const T& pItemToInsert, const T& pItemToBeInsertedAfter)
		{
			typename SList<T>::Iterator itr = Find(pItemToBeInsertedAfter);
			if (itr != end())
			{
				return InsertAfter(pItemToInsert, itr);
			}
			return end();
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::InsertAfter(const T & pItemToInsert, Iterator pIteratorToBeInsertedAfter)
		{
			if (pIteratorToBeInsertedAfter.mOwnerList == this)
			{
				if (pIteratorToBeInsertedAfter != end())
				{
					Node* nodeNextToTargetElement = pIteratorToBeInsertedAfter.mNode->mNextNode;
					Node* node = new Node(pItemToInsert, nodeNextToTargetElement);
					pIteratorToBeInsertedAfter.mNode->mNextNode = node;
					mSize++;
					return SList<T>::Iterator(this, node);
				}
				else
				{
					//TODO: consider doing push back
					throw exception("Cannot insert after end.");
				}
			}
			else
			{
				throw exception("Iterator doesn't belong to the list.");
			}
		}


		template<typename T>
		typename SList<T>::Iterator SList<T>::begin() const
		{
			return SList<T>::Iterator(this, mFrontNode);
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::end() const
		{
			return SList<T>::Iterator(this, nullptr);
		}

#pragma region Iterator
		// iterator class members implementation
		template<typename T>
		SList<T>::Iterator::Iterator(const SList<T>* pOwnerList, Node* pCurrentNode) : mOwnerList(pOwnerList), mNode(pCurrentNode)
		{}

		template<typename T>
		SList<T>::Iterator::Iterator() : mOwnerList(nullptr), mNode(nullptr)
		{}

		template<typename T>
		SList<T>::Iterator::Iterator(typename const SList<T>::Iterator& pIterator) : mOwnerList(pIterator.mOwnerList), mNode(pIterator.mNode)
		{}

		template<typename T>
		typename SList<T>::Iterator& SList<T>::Iterator::operator=(typename const SList<T>::Iterator& pOther)
		{
			if (this != &pOther)
			{
				this->mNode = pOther.mNode;
				this->mOwnerList = pOther.mOwnerList;
			}
			return *this;
		}

		template<typename T>
		bool SList<T>::Iterator::operator ==(typename const SList<T>::Iterator& pOther) const
		{
			return (mOwnerList == pOther.mOwnerList) && (mNode == pOther.mNode);
		}

		template<typename T>
		bool SList<T>::Iterator::operator !=(typename const SList<T>::Iterator& pOther) const
		{
			return !(*this == pOther);
		}

		template<typename T>
		typename SList<T>::Iterator& SList<T>::Iterator::operator ++()
		{
			if (mNode)
			{
				mNode = mNode->mNextNode;
				return (*this);
			}
			// if current node is null that means iterator reached end of list
			throw exception("Cannot increment iterator. Reached end of list.");
		}

		template<typename T>
		typename SList<T>::Iterator SList<T>::Iterator::operator ++(int32_t)
		{
			SList::Iterator tmp(*this);
			operator++();
			return tmp;
		}

		template<typename T>
		T& SList<T>::Iterator::operator *()
		{
			if (mNode)
			{
				return mNode->mData;
			}
			// if mCurrentNode is null, that mean the iterator is the end iterator.
			throw exception("Cannot dereference end iterator.");
		}

		template<typename T>
		const T& SList<T>::Iterator::operator *() const
		{
			if (mNode)
			{
				return mNode->mData;
			}
			// if mCurrentNode is null, that mean the iterator is the end iterator.
			throw exception("Cannot dereference end iterator.");
		}
#pragma endregion
	}
}