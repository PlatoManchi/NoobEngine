#pragma once

#include "Vector.h"

namespace NoobEngine
{
	namespace Container
	{
#pragma region Iterator
		template<typename T>
		Vector<T>::Iterator::Iterator(const Vector* pOwnerVector, uint32_t pIndex) :
			mOwnerVector(pOwnerVector), mIndex(pIndex)
		{}

		template<typename T>
		Vector<T>::Iterator::Iterator(typename const Vector<T>::Iterator& pIterator) :
			Iterator(pIterator.mOwnerVector, pIterator.mIndex)
		{}

		template<typename T>
		typename Vector<T>::Iterator& Vector<T>::Iterator::operator =(typename const Vector<T>::Iterator& pOther)
		{
			if (this != &pOther)
			{
				mOwnerVector = pOther.mOwnerVector;
				mIndex = pOther.mIndex;
			}

			return *this;
		}

		template<typename T>
		bool Vector<T>::Iterator::operator ==(typename const Vector<T>::Iterator& pOther) const
		{
			return (mOwnerVector == pOther.mOwnerVector) && (mIndex == pOther.mIndex);
		}

		template<typename T>
		bool Vector<T>::Iterator::operator !=(typename const Vector<T>::Iterator& pOther) const
		{
			return !(*this == pOther);
		}

		template<typename T>
		typename Vector<T>::Iterator& Vector<T>::Iterator::operator ++()
		{
			if (mIndex >= mOwnerVector->mSize)
			{
				mIndex++;
				return *this;
			}
			throw exception("Cannot increment iterator. Reached end of vector.");
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::Iterator::operator ++(int32_t)
		{
			Vector::Iterator tmp(*this);
			++(*this);
			return tmp;
		}

		template<typename T>
		T& Vector<T>::Iterator::operator *()
		{
			if (mIndex >= 0 && mIndex < mOwnerVector->mSize)
			{
				return mOwnerVector[mIndex];
			}

			throw exception("Cannot dereference end iterator.");
		}

		template<typename T>
		const T& Vector<T>::Iterator::operator *() const
		{
			return *(*this);
		}
#pragma endregion

#pragma region Vector
		template<typename T>
		Vector<T>::Vector() : 
			mData(nullptr), mSize(0), mCapacity(_DEFAULT_INIT_CAPACITY_)
		{
			Reserve(mCapacity);
		}

		template<typename T>
		Vector<T>::Vector(const Vector& pOther) :
			mData(nullptr), mSize(0), mCapacity(pOther.mSize)
		{
			Reserve(mCapacity);
		}

		template<typename T>
		Vector<T>::Vector(const uint32_t pCapacity) :
			mData(nullptr), mSize(0), mCapacity(pCapacity)
		{
			Reserve(mCapacity);
		}

		template<typename T>
		Vector<T>::~Vector()
		{}

		template<typename T>
		T& Vector<T>::Front()
		{
			return operator[0];
		}

		template<typename T>
		const T& Vector<T>::Front() const
		{
			return operator[0];
		}

		template<typename T>
		T & Vector<T>::Back()
		{
			return operator[mSize - 1];
		}

		template<typename T>
		const T & Vector<T>::Back() const
		{
			return operator[mSize - 1];
		}

		template<typename T>
		T Vector<T>::PopBack()
		{
			return T();
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::PushBack(const T & pData)
		{
			return Iterator();
		}

		template<typename T>
		T& Vector<T>::At(uint32_t pIndex) const
		{
			return operator[pIndex];
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::Find(const T & pObject) const
		{
			return Iterator();
		}

		template<typename T>
		void Vector<T>::Remove(const T& pObject)
		{}

		template<typename T>
		void Vector<T>::Remove(const Iterator & pBegin, const Iterator & pEnd)
		{}

		template<typename T>
		void Vector<T>::Reserve(uint32_t pCapacity)
		{
			if (mCapacity == pCapacity)
			{
				// if current capacity is same as wanted capacity then do nothing.
				return;
			}
			if (pCapacity < mSize)
			{
				pCapacity = mSize;
			}
			T* mPrevData = mData;
			mData = static_cast<T*>(malloc(sizeof(T) * pCapacity));

			if (mSize != 0)
			{
				
			}
		}

		template<typename T>
		void Vector<T>::Clear()
		{}

		template<typename T>
		bool Vector<T>::IsEmpty() const
		{
			return (mSize == 0);
		}

		template<typename T>
		uint32_t Vector<T>::Size() const
		{
			return mSize;
		}

		template<typename T>
		uint32_t Vector<T>::Capacity() const
		{
			return mCapacity;
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::begin() const
		{
			return Iterator(this, 0);
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::end() const
		{
			return Iterator(this, mSize);
		}

		template<typename T>
		T & Vector<T>::operator[](uint32_t pIndex)
		{
			if (pIndex < mSize)
			{
				return mData[pIndex];
			}
			else
			{
				throw exception("IndexOutOfBounds");
			}
		}

		template<typename T>
		const T & Vector<T>::operator[](uint32_t pIndex) const
		{
			return operator[pIndex];
		}
#pragma endregion
	}
}