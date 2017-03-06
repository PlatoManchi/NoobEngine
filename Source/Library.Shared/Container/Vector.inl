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
		bool Vector<T>::Iterator::operator > (typename const Vector<T>::Iterator& pOther) const
		{
			return mIndex > pOther.mIndex;
		}

		template<typename T>
		bool Vector<T>::Iterator::operator < (typename const Vector<T>::Iterator& pOther) const
		{
			return !(*this > pOther);
		}

		template<typename T>
		typename Vector<T>::Iterator& Vector<T>::Iterator::operator ++()
		{
			if (!mOwnerVector)
			{
				throw std::exception("Invalid iterator.");
			}
			if (mIndex <= mOwnerVector->mSize)
			{
				mIndex++;
				return *this;
			}
			throw std::exception("Cannot increment iterator. Reached end of vector.");
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
				return mOwnerVector->mData[mIndex];
			}

			throw std::exception("Cannot dereference end iterator.");
		}

		template<typename T>
		const T& Vector<T>::Iterator::operator *() const
		{
			return *(*this);
		}
#pragma endregion

#pragma region Vector
#pragma region ConstructorsDestructor
		template<typename T>
		Vector<T>::Vector() : 
			mData(nullptr), mSize(0), mCapacity(0), mCapacityIncrementStep(_DEFAULT_INCEMENENT_STEP_)
		{
			Reserve(_DEFAULT_INIT_CAPACITY_);
		}

		template<typename T>
		Vector<T>::Vector(const Vector& pOther) :
			Vector(pOther.mCapacity, pOther.mCapacityIncrementStep)
		{
			Reserve(mCapacity);
			
			for each (T element in pOther)
			{
				PushBack(element);
			}
		}

		template<typename T>
		Vector<T>::Vector(const Vector&& pOther)
		{
			mData = pOther.mData;
			mSize = pOther.mSize;
			mCapacity = pOther.mCapacity;
			mCapacityIncrementStep = pOther.mCapacityIncrementStep;

			pOther.mData = nullptr;
			pOther.mSize = 0U;
			pOther.mCapacity = 0U;
		}

		template<typename T>
		Vector<T>::Vector(const uint32_t pCapacity, uint32_t pCapacityIncrementStep) :
			mData(nullptr), mSize(0), mCapacity(0), mCapacityIncrementStep(pCapacityIncrementStep)
		{
			Reserve(pCapacity);
		}

		template<typename T>
		Vector<T>::~Vector()
		{
			Clear();
		}

#pragma endregion
		template<typename T>
		T& Vector<T>::Front()
		{
			return operator[](0);
		}

		template<typename T>
		const T& Vector<T>::Front() const
		{
			return operator[](0);
		}

		template<typename T>
		T & Vector<T>::Back()
		{
			return operator[](mSize - 1);
		}

		template<typename T>
		const T& Vector<T>::Back() const
		{
			return operator[](mSize - 1);
		}

		template<typename T>
		T Vector<T>::PopBack()
		{
			if (mSize > 0)
			{
				T tmp = mData[--mSize];
				mData[mSize].~T();
				return tmp;
			}
			throw std::exception("Cannot pop on empty vector");
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::PushBack(const T& pData)
		{
			if (mSize == mCapacity)
			{
				// if capacity is reached, allocate reserve more memory.
				Reserve(mCapacity + mCapacityIncrementStep);
			}
			// using placement new to use the buffer created during Rserve().
			// calling copy constructor on T to make sure that the ownership is true to this vector.
			new (mData + mSize++)T(pData);
			
			return Iterator(this, mSize - 1);
		}

		template<typename T>
		T& Vector<T>::At(uint32_t pIndex) const
		{
			return operator[](pIndex);
		}

		template<typename T>
		typename Vector<T>::Iterator Vector<T>::Find(const T & pObject) const
		{
			for (typename Vector<T>::Iterator itr = begin(); itr != end(); ++itr)
			{
				if (*itr == pObject)
				{
					return itr;
				}
			}
			return end();
		}

		template<typename T>
		void Vector<T>::Remove(const T& pObject)
		{
			Iterator itr = Find(pObject);
			if (itr != end())
			{
				++itr;
				// shift all elements to left by once
				for (; itr != end() ; ++itr)
				{
					// by using assignment in to left element instead of deleting and creating copy is avoiding allocations.
					mData[itr.mIndex - 1] = *itr;
				}

				--mSize;

				// delete the last element
				(mData[mSize]).~T();
			}
		}

		template<typename T>
		void Vector<T>::Remove(Iterator pBegin, Iterator pEnd)
		{
			if (pBegin.mOwnerVector != this || pEnd.mOwnerVector != this)
			{
				throw std::exception("Invalid iterators.");
			}
			if (pBegin > pEnd)
			{
				// if the order of the iterators are in reverse swap them and call remove
				Remove(pEnd, pBegin);
			}

			// calling remove from here can cause performance loss since remove has O(n) in worst case.
			// deleting all elements at once and shifting can give a significant performance boost
			uint32_t itemsToDelete = pEnd.mIndex - pBegin.mIndex;
			
			for (; pEnd != end(); ++pEnd)
			{
				*pBegin = *pEnd;
				++pBegin;
			}

			// by end of previous loop the beginItr will be pointing to the position where excess remaining elements.
			for (; pBegin != end(); ++pBegin)
			{
				(*pBegin).~T();
			}

			mSize = mSize - itemsToDelete;
		}

		template<typename T>
		void Vector<T>::Reserve(uint32_t pCapacity)
		{
			if (mCapacity == pCapacity)
			{
				// if current capacity is same as required capacity then do nothing.
				return;
			}
			if (pCapacity < mSize)
			{
				// if capacity is less than size then do shrink to fit
				pCapacity = mSize;
			}
			T* mPrevData = mData;
			mData = static_cast<T*>(malloc(sizeof(T) * pCapacity));

			if (!mData)
			{
				throw std::exception("Unable to create memory.");
			}

			if (mPrevData)
			{
				memcpy(mData, mPrevData, sizeof(T) * mSize);
				free(mPrevData);
			}

			// if successfully allocated memory, make current capacity as pCapacity
			mCapacity = pCapacity;
		}

		template<typename T>
		void Vector<T>::Reserve(ReserveFunction& pReserveFunction)
		{
			Reserve(pReserveFunction(mSize, mCapacity));
		}

		template<typename T>
		void Vector<T>::Clear()
		{
			for each (T& element in *this)
			{
				element;
				(element).~T();
			}
			
			mSize = 0;
			mCapacity = 0;
			free(mData);
			mData = nullptr;
		}

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
		uint32_t Vector<T>::GetCapacityIncrementStep() const
		{
			return mCapacityIncrementStep;
		}

		template<typename T>
		void Vector<T>::SetCapacityIncrementStep(uint32_t pCapacityIncrementStep)
		{
			mCapacityIncrementStep = pCapacityIncrementStep;
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
		Vector<T>& Vector<T>::operator=(const Vector<T> & pOther)
		{
			if (this != &pOther)
			{
				Clear();
				Reserve(pOther.mCapacity);

				for each (T element in pOther)
				{
					PushBack(element);
				}
			}
			return *this;
		}

		template<typename T>
		Vector & Vector<T>::operator=(const Vector && pOther)
		{
			mData = pOther.mData;
			mSize = pOther.mSize;
			mCapacity = pOther.mCapacity;
			mCapacityIncrementStep = pOther.mCapacityIncrementStep;

			pOther.mData = nullptr;
			pOther.mSize = 0U;
			pOther.mCapacity = 0U;

			return *this;
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
				throw std::exception("IndexOutOfBounds");
			}
		}

		template<typename T>
		const T & Vector<T>::operator[](uint32_t pIndex) const
		{
			if (pIndex < mSize)
			{
				return mData[pIndex];
			}
			else
			{
				throw std::exception("IndexOutOfBounds");
			}
		}
#pragma endregion
	}
}