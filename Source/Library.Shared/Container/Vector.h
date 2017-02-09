#pragma once

#include "../pch.h"

#define _DEFAULT_INIT_CAPACITY_ 10
#define _DEFAULT_INCEMENENT_STEP_ 5

namespace NoobEngine
{
	namespace Container
	{
		
		/**
			The elements of a vector are stored contiguously. Vectors allow the user to denote an initial capacity for the container. Vectors also allow random access; that is, an element of a vector may be referenced in the same manner as elements of arrays (by array indices).
		*/
		
		template <typename T>
		class Vector final
		{
		public:
			class ReserveFunction
			{
			public:
				ReserveFunction() {};
				virtual uint32_t operator() (uint32_t pSize, uint32_t pCapacity) {
					pSize;
					return pCapacity + _DEFAULT_INCEMENENT_STEP_;
				}
			};

			class Iterator final
			{
				friend class Vector;
				
			public:
				/**
					@brief Copy constructor for creating new iterator using existing iterator.
					@param pIterator Constant reference to which a copy has to be created.
				*/
				Iterator(const Iterator& pIterator);
				
				/**
					@brief Assign the rhs value to lhs iterator.
					@param pOther Iterator to create copy of.
					@return Iterator reference.
				*/
				Iterator& operator=(const Iterator& pOther);

				/**
					@brief Check if two iterator are equal
					@param pOther Iterator to compare this iterator with.
					@return boolean. true if equal. false if not equal.
					@see operator!=()
				*/
				bool operator==(const Iterator& pOther) const;

				/**
					@brief Check if two iterators are not equal
					@param pOther Iterator to compare this iterator with.
					@return boolean. true if not equal. false if equal.
					@see operator==()
				*/
				bool operator!=(const Iterator& pOther) const;

				/**
					@brief Check if this iterator is pOther iterator is pointing to element that is on right side of element current iterator is pointing to.
					@param pOther Iterator to compare with
					@return Boolean. true if greater else false.
				*/
				bool operator>(const Iterator& pOther) const;

				/**
					@brief Check if this iterator is pOther iterator is pointing to element that is on left side of element current iterator is pointing to.
					@param pOther Iterator to compare with
					@return Boolean. true if lesser else false.
				*/
				bool operator<(const Iterator& pOther) const;

				/**
					@brief Pre-increment the iterator to point to next item in vector.
					@details If the iterator is pointing to the end of the vector, invoking this operator will result in exception being thrown.
					@return Reference to iterator that points to next element in the vector.
					@see operator++()
				*/
				Iterator& operator++();

				/**
					@brief Post-increment the iterator to point to next item in vector.
					@details If the iterator is pointing to the end of the vector, invoking this operator will result in exception being thrown.
					@return Reference to current iterator, the invoked iterator will points to next element in the vector.
					@see operator++()
				*/
				Iterator operator++(int32_t);

				/**
					@brief Dereference the iterator to return the reference to the data its pointing to.
					@details If the iterator is pointing to the end of the vector, invoking this operator will result in exception being thrown.
					@return Reference to the data iterator is pointing to.
					@see operator*()
				*/
				T& operator*();

				/**
					@brief Deference the iterator to return the constant reference the data its pointing to.
					@details If the iterator is pointing to the end of the vector, invoking this operator will result in exception being thrown.
					@return Constant reference to the data iterator is point to.
					@see operator*()
				*/
				const T& operator*() const;

				/**
					@brief Constructor for creating new iterator.
					@param pOwnerVector Constant pointer to the list that owns the iterator.
					@param pIndex Index of the element this iterator is pointing to.
				*/
				Iterator(const Vector<T>* pOwnerVector, uint32_t pIndex);

			private:

				/**
					Pointer to the owner vector to which this iterator belongs to.
				*/
				const Vector* mOwnerVector;

				/**
					Index of the element this iterator is pointing to.
				*/
				uint32_t mIndex;
			};

			/**
				@brief Create an empty vector with default capacity.
				@see Vector()
			*/
			Vector();

			/**
				@brief Create a new vector with exact same data as the vector that is passed.
				@param pOther Vector that is supposed to be deep copied.
				@see Vector()
			*/
			Vector(const Vector& pOther);

			/**
				@brief Create a new vector with capacity passed as parameter.
				@param pCapacity Initial capacity that the vector should contain.
				@see Vector()
			*/
			Vector(const uint32_t pCapacity, uint32_t pCapacityIncrementStep = _DEFAULT_INCEMENENT_STEP_);

			/**
				@brief Standard destructor.
			*/
			~Vector();

			/**
				@brief Returns reference to the first element in the vector.
				@details Changing the value of the reference will effect the actual value in the list. Throws exception if called on empty vector.
				@return Reference to the first element in the list.
				@see Front()
				@see Back()
			*/
			T& Front();

			/**
				@brief Returns constant reference to the first element in the vector.
				@details Changing the value of the reference will effect the actual value in the vector. Throws exception if called on empty vector.
				@return Constant reference to the first element in the vector.
				@see Front()
				@see Back()
			*/
			const T& Front() const;

			/**
				@brief Returns reference to the last element in the vector.
				@details Changing the value of the reference will effect the actual value in the vector. Throws exception if called on empty vector.
				@return Reference to the last element in the vector.
				@see Front()
				@see Back()
			*/
			T& Back();

			/**
				@brief Returns constant reference to the last element in the vector.
				@details Changing the value of the reference will effect the actual value in the vector. Throws exception if called on empty vector.
				@return Constant reference to the last element in the vector.
				@see Front()
				@see Back()
			*/
			const T& Back() const;

			/**
				 @brief Return the last element of the vector.
				 @details THrows exception if vector is empty
				 @return Return the first element int he list. Same type as the list.
			*/
			T PopBack();

			/**
				@brief Push the data at the end of vector.
				@param pData Data that needs to be pushed at end of vector.
				@return Iterator that points to the data that was pushed.
			*/
			Iterator PushBack(const T& pData);

			/**
				@brief Return reference of the variable that is at the passed index of the vector.
				@details If the index is not valid, it will throw exception.
				@param pIndex Index at which the element should be.
				@return Reference to the element at pIndex-th position.
			*/
			T& At(uint32_t pIndex) const;

			/**
				@brief Return iterator for the first element that matches with the object passed to the function.
				@details It returns end iterator if the element is not found or if the vector is empty.
				@param pObject The element that needs to be searched for in the vector
				@return Iterator object that points to pObject in the vector or end iterator if element is not found.
			*/
			Iterator Find(const T& pObject) const;

			/**
				@brief Searches for the element and if found, will remove the element from the vector.
				@details If the element is not found nothing will happen to the vector.
				@param pObject The element that needs to be removed from the vector.
			*/
			void Remove(const T& pObject);

			/**
				@brief Starts at the element that pBegin points to and delete all elements till pEnd.
				@details pBegin has to be an iterator that is greater than pEnd.
				@param pBegin Iterator that points to the starting point from which elements needs to be deleted.
				@param pEnd Iterator that points to the ending point till which elements need to be deleted.
			*/
			void Remove(Iterator pBegin, Iterator pEnd);

			/**
				@brief Increases the capacity of the vector.
				@details If pCapacity is less than current capacity, vector will be shrunk. If pCapacity is less than size, vector will be shrunk to fit current size of vector.
				@param pCapacity The value to which capacity needs to be adjusted.
			*/
			void Reserve(uint32_t pCapacity);

			/**
				@brief Increases the capacity of the vector based on the helper function that is passed.
				@details If pCapacity is less than current capacity, vector will be shrunk. If pCapacity is less than size, vector will be shrunk to fit current size of vector.
				@param pReserveFunction The functor that will be called to get the capacity size.
			*/
			void Reserve(ReserveFunction& pReserveFunction);

			/**
				@brief Delete all elements from he vector. Makes size and capacity of the vector 0.
			*/
			void Clear();

			/**
				@brief Check if vector is empty or not.
				@return Boolean. True id empty, False if not
			*/
			bool IsEmpty() const;

			/**
				@brief Get the size of the vector.
				@return unsigned int that holds the size of the vector.
			*/
			uint32_t Size() const;

			/**
				@brief Get the capacity of the vector.
				@return unsigned int that holds the capacity of the vector.
			*/
			uint32_t Capacity() const;

			/**
				@brief Get capacity increment step.
				@return unsigned int that holds the step at which capacity will be incremented if needed.
			*/
			uint32_t GetCapacityIncrementStep() const;

			/**
				@brief Set capacity increment step.
				@param pCapacityIncrementStep unsigned in to which capacity increment step should be set as.
			*/
			void SetCapacityIncrementStep(uint32_t pCapacityIncrementStep);

			/**
				@brief Return the iterator that points to the first element in the vector.
				@details If the vector is empty this will be same as the iterator end().
				@return Iterator that points to the first element in the vector.
				@see end()
			*/
			Iterator begin() const;

			/**
				@brief Return the iterator that points the last element in the vector.
				@details If the list is empty this will be same as the iterator pointing to the beginning of the vector.
				@return Iterator that points to the last element in the vector.
				@see begin()
			*/
			Iterator end() const;

			/**
				@brief Does a deep copy of all the list elements into new vector.
				@param pOther Deep copy the rhs vector into lhs vector.
				@return Reference to the vector.
			*/
			Vector& operator=(const Vector& pOther);

			/**
				@brief Index of operator that returns the reference of data that is stored at particular index.
				@details This is random access.
				@param pIndex The index of the element. If the index is greater than the size it will throw exception.
				@return Returns the reference of the data.
				@see operator[]()
			*/
			T& operator[](uint32_t pIndex);

			/**
				@brief Index of operator that returns the constant reference of data that is stored at particular index.
				@details This is random access.
				@param pIndex The index of the element. If the index is greater than the size it will throw exception.
				@return Returns the constant reference of the data.
				@see operator[]()
			*/
			const T& operator[](uint32_t pIndex) const;
		private:
			/**
				Pointer that holds the array that contains the data in vector
			*/
			T* mData;

			/**
				Holds the number of elements in the vector.
				@see Size()
			*/
			uint32_t mSize;

			/**
				Holds the capacity of the vector. Size will always be less than capacity.
			*/
			uint32_t mCapacity;

			/**
				Stores the step at which capacity is incremented.
			*/
			uint32_t mCapacityIncrementStep;
		};
	}
}

#include "Vector.inl"