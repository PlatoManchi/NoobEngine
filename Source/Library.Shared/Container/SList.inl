
#include "SList.h"

using namespace std;

namespace FIEAGameEngine::Container
{
	
	template <class T>
	SList<T>::SList() :
		mFrontNode(nullptr), mBackNode(nullptr), mSize(0)
	{

	}

	template <class T >
	SList<T>::SList(const SList& pList) :
		mFrontNode(nullptr), mBackNode(nullptr), mSize(0)
	{
		Node* nextNode = pList.mFrontNode;
		while (nextNode)
		{
			PushBack(nextNode->mData);
			nextNode = nextNode->mNextNode;
		}
	}

	template <class T>
	SList<T>::SList(const SList* pList) :
		mFrontNode(nullptr), mBackNode(nullptr), mSize(0)
	{
		Node* nextNode = pList->mFrontNode;
		while (nextNode)
		{
			PushBack(nextNode->mData);
			nextNode = nextNode->mNextNode;
		}
	}

	template <class T>
	SList<T>::~SList()
	{
		Clear();
	}

	template <class T>
	SList<T>& SList<T>::operator=(const SList& pList)
	{
		// making sure that assignment operator is not called on itself
		if (this != &pList)
		{
			// clear all the previous elements held by the current list
			this->Clear();

			if (pList.mSize != 0)
			{
				Node* nextNode = pList.mFrontNode;
				do
				{
					PushBack(nextNode->mData);
					nextNode = nextNode->mNextNode;
				} while (nextNode);
			}
		}
		
		return *this;
	}

	template <class T>
	void SList<T>::PushFront(const T& pData)
	{
		Node* node = new Node;
		node->mData = pData;

		if (mFrontNode)
		{
			node->mNextNode = mFrontNode;
			mFrontNode = node;
		} else
		{
			// empty list
			mFrontNode = node;
			mBackNode = node;
		}

		mSize++;
	}

	template <class T>
	void SList<T>::PushBack(const T& pData)
	{
		Node* node = new Node;
		node->mData = pData;

		if (mFrontNode)
		{
			mBackNode->mNextNode = node;
			mBackNode = node;
		} else
		{
			// empty list
			mFrontNode = node;
			mBackNode = node;
		}
		mSize++;
	}

	template <class T>
	T SList<T>::PopFront()
	{
		if (mSize == 0)
		{
			throw exception("Calling Pop on empty list.");
		}

		// saving reference of front node and the data in temp variables
		Node* frontNode = mFrontNode;
		T data = frontNode->mData;

		mFrontNode = mFrontNode->mNextNode;
		delete(frontNode);

		mSize--;

		return data;
	}

	template <class T>
	T& SList<T>::Front()
	{
		if (mSize == 0)
		{
			throw exception("Calling Front on empty list.");
		}

		return mFrontNode->mData;
	}

	template <class T>
	T& SList<T>::Front() const
	{
		if (mSize == 0)
		{
			throw exception("Calling Front on empty list.");
		}

		return mFrontNode->mData;
	}

	template <class T>
	T& SList<T>::Back()
	{
		if (mSize == 0)
		{
			throw exception("Calling Back on empty list.");
		}

		return mBackNode->mData;
	}

	template <class T>
	T& SList<T>::Back() const
	{
		if (mSize == 0)
		{
			throw exception("Calling Back on empty list.");
		}

		return mBackNode->mData;
	}

	template <class T>
	void SList<T>::Clear()
	{
		while (mSize != 0)
		{
			PopFront();
		}
	}

	template <class T>
	uint32_t SList<T>::Size() const
	{
		return mSize;
	}

	template <class T>
	bool SList<T>::IsEmpty() const
	{
		return (mFrontNode == nullptr);
	}
}