#pragma once
#include "../pch.h"
#include "Vector.h"
#include "SList.h"
#include <string>

namespace NoobEngine
{
	namespace Container
	{
		template <typename T>
		class DefaultHashFunction
		{
		public:
			DefaultHashFunction() {}
			uint32_t operator()(T pParam);
		};
		
		template <>
		class DefaultHashFunction <char*>
		{
		public:
			DefaultHashFunction() {}
			uint32_t operator()(const char* pParam);
		};

		template <>
		class DefaultHashFunction <std::string>
		{
		public:
			DefaultHashFunction() {}
			uint32_t operator()(std::string pParam);
		};

		/**
		Hash map is a data structure used to implement an associative array, a structure that can map keys to values. A hash table uses a hash function to compute an index into an array of buckets or slots, from which the desired value can be found.
		*/
		template <typename TKey, typename TValue, typename HashFunctor = DefaultHashFunction<TKey>>
		class Hashmap
		{
			typedef Vector<SList<std::pair<TKey, TValue>>> BucketType;
			/*class BucketType;
			class BucketType::Iterator;
			friend class BucketType;
			friend class BucketType::Iterator;*/
		public:
			class Iterator
			{
				friend class Hashmap;
				
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
				Iterator& operator=(const Iterator& pOther) = default;

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
				std::pair<TKey, TValue>& operator*();

				/**
					@brief Deference the iterator to return the constant reference the data its pointing to.
					@details If the iterator is pointing to the end of the vector, invoking this operator will result in exception being thrown.
					@return Constant reference to the data iterator is point to.
					@see operator*()
				*/
				const std::pair<TKey, TValue>& operator*() const;
			private:
				/**
					Holds the iterator that points to the bucket
				*/
				typename Vector<SList<std::pair<TKey, TValue>>>::Iterator mHorizontalIterator;

				/**
					Holds iterator for the list in particular bucket
				*/
				typename SList<std::pair<TKey, TValue>>::Iterator mVerticalIterator;

				/**
					Owner hashmap.
				*/
				const Hashmap* mOwner;

				Iterator(const Hashmap* pOwner, typename BucketType::Iterator pIteratorToBucket, typename SList<std::pair<TKey, TValue>>::Iterator pIteratorToPair);
			};

			/**
				@brief Constructor to create a hash map. Bigger the size of hash map better the performance.
				@details The bigger the bucket size the better search and indexing performance.
				@param pHashmapBucketSize Unsigned int that holds the bucket size used by the hash map.
			*/
			explicit Hashmap(uint32_t pHashmapBucketSize = 11);

			/**
				@brief Copy constructor that deep copies everything from one hashmap into another hash map.
				@param pOther Reference to the hash map that needs to be copied.
			*/
			Hashmap(const Hashmap& pOther);

			/**
				@brief Delete all the elements form the hash map and clear the memory used by the hash map.
			*/
			~Hashmap();

			/**
				@brief Search if the key is there in the hash map and return the iterator that points to particular object.
				@param pKey The key to find in the hash map.
			*/
			Iterator Find(const TKey& pKey) const;

			/**
				@brief Inserts the given key value pair into the hash map. If the key already exists returns a iterator that points to the existing key value pair.
				@param pKeyValuePair Reference to the key value pair that needs to be inserted into hash map.
			*/
			Iterator Insert(std::pair<TKey, TValue>& pKeyValuePair);

			/**
				@brief Search for element with key value and removes the value from hash map.
				@details If the key is not found then nothing happens
				@param pKey The key that needs to be removed from hash map.
			*/
			void Remove(const TKey& pKey);

			/**
				@brief Delete all elements from the hash map and clear the memory being used.
			*/
			void Clear();

			/**
				@brief Return the count of key value pairs in the hash map.
			*/
			uint32_t Size() const;

			/**
				@brief Searches for the key in the hash map and return true if the key is present or false if not.
				@param The key for which to search for in the hash map.
			*/
			bool ContainsKey(const TKey& pKey) const;

			/**
				@brief Return the Iterator that points to the first element in the iterator.
			*/
			Iterator begin() const;

			/**
				@brief Return the iterator that points to the last element in the iterator.
			*/
			Iterator end() const;

			/**
				@brief Does a deep copy all elements from the reference object into new hash map.
				@param pOther Deep copy the rhs hash map into the lhs hash map
				@return Reference to the hash map
			*/
			Hashmap& operator=(const Hashmap& pOther) = default;

			/**
				@brief Return value associated with the key.
				@details If the key is not present then it return a reference to a default object of TValue type.
				@param pKey the key that needs to be associated with the value
				@return Reference to the value associated with the key.
			*/
			TValue& operator[](const TKey& pKey);

			/**
				@brief Return value associated with the key.
				@details If the key is not present then it return a reference to a default object of TValue type.
				@param pKey the key that needs to be associated with the value
				@return Constant reference to the value associated with the key.
			*/
			const TValue& operator[](const TKey& pKey) const;
		private:

			/**
				Stores the count of elements in the iterator.
				@see Size()
			*/
			uint32_t mSize;

			/**
				Saving the hash functor
			*/
			HashFunctor mHashFunctor;

			/**
				Stores the data
			*/
			BucketType mData;
		};
	}
}

#include "Hashmap.inl"