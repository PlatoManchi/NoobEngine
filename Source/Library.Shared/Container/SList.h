#pragma once
#include "../pch.h"
namespace NoobEngine
{
	namespace Container
	{
		/**
			SList is dynamic sized container class that implements singly linked list.
		*/
		template <typename T>
		class SList final
		{
			// forward declaring private nested classes 
			class Node;

		public:
			// forward declaring public nested classes
			class Iterator;

			/**
				@brief Create a empty singly list.
				@see SList()
			*/
			SList();

			/**
				@brief Deep copy all elements from reference object into new list
				@param pList Deep copy the constructor passed as parameter
				@see SList()
			*/
			SList(const SList& pList);
			
			/**
				@brief Move semantics. Steals the data from passed SList and nullify the passed SList.
				@param pList SList from which to steal the data.
			*/
			SList(SList&& pList);

			/**
				@brief Standard destructor.
			*/
			~SList();

			/**
				@brief Does a deep copy of all the list elements into new list.
				@param pList Deep copy the rhs list into lhs list.
				@return Reference to the list.
			*/
			SList& operator=(const SList& pList);

			/**
				@brief Move semantics. Steals the data from passed SList and nullify the passed SList.
				@param pList SList from which to steal the data.
			*/
			SList& operator=(SList&& pList);

			/**
				@brief Insert the data at front of the list.
				@param The data that need to be pushed.
				@return Begin iterator.
			*/
			Iterator PushFront(const T& pData);

			/**
				@brief Append data at end of the list.
				@param The data that need to be pushed.
				@return End iterator.
			*/
			Iterator PushBack(const T& pData);


			/**
				@brief Pop the first element of the list.
				@details Throws exception with message "Calling Pop on empty list." if list is empty.
				@return Return the first element in the list. Same type as the list.
			*/
			T PopFront();

			/**
				@brief Return reference to the first element in the list.
				@details Changing the value of reference will effect the actual value in the list. Throws exception with message "Calling Front on empty list." if called on empty list
				@return Reference to the first element in the list.
				@see Front()
				@see Back()
			*/
			T& Front();

			/**
				@brief Return constant reference to the first element in the list.
				@details Changing the value of reference will effect the actual value in the list. Throws exception with message "Calling Front on empty list." if called on empty list
				@return Constant reference to the first element in the list.
				@see Front()
				@see Back()
			*/
			const T& Front() const;

			/**
				@brief Return reference to the last element in the list.
				@details Changing the value of reference will effect the actual value in the list. Throws exception with message "Calling Back on empty list." if called on empty list
				@return Reference to the last element in the list.
				@see Front()
				@see Back()
			*/
			T& Back();

			/**
				@brief Return constant reference to the last element in the list.
				@details Changing the value of reference will effect the actual value in the list. Throws exception with message "Calling Back on empty list." if called on empty list
				@return Constant reference to the last element in the list.
				@see Front()
				@see Back()
			*/
			const T& Back() const;

			/**
				@brief Remove all the elements from list.
			*/
			void Clear();

			/**
				@brief Return the size of the list.
				@return unsigned int that holds the size of list.
			*/
			std::uint32_t Size() const;

			/**
				@brief Returns if the list is empty or not.
				@return boolean. true if empty. false if not empty.
			*/
			bool IsEmpty() const;

			/**
				@brief Search for the object that is passed as parameter and return the iterator that points to the object in the list.
				@details If the object is not fount, it returns the iterator that points to the end of the list.
				@return Iterator that points to the object if found, else Iterator that points to the end of list.
			*/
			Iterator Find(const T& pObject) const;

			/**
				@brief Search for the object and remove the object from the list.
			*/
			void Remove(const T& pObject);

			/**
				@brief Insert the given element after the specified element.
				@details If the specified element is not found then the item will not be inserted.
				@param pItemToInsert The item that needs to be inserted into the list.
				@param pItemToBeInsertedAfter The item that pItemToInsert should be inserted after.
				@return Iterator that points to the current inserted value. If the value is not found then it return end iterator.
			*/
			Iterator InsertAfter(const T& pItemToInsert, const T& pItemToBeInsertedAfter);

			/**
				@brief Insert the given element after the specified iterator.
				@details If the iterator doesn't belong to the current slist then throw exception. If the iterator is end it will throw exception.
				@param pItemToInsert The item that needs to be inserted into the list.
				@param pIteratorToBeInsertedAfter The item that pItemToInsert should be inserted after.
				@return Iterator that points to the current inserted value.
			*/
			Iterator InsertAfter(const T& pItemToInsert, Iterator pIteratorToBeInsertedAfter);

			/**
				Iterator used to loop through the SList.
			*/
			class Iterator final
			{
				friend class SList;
			public:
				/**
					@brief Default constructor
				*/
				Iterator();

				/**
					@brief Copy constructor for creating new iterator.
					@param pIterator const reference to which a copy has to be created.
				*/
				Iterator(const Iterator& pIterator);

				/**
					@brief Assign the rhs value lhs iterator.
					@param pOther iterator to create copy of.
					@return Iterator reference.
				*/
				Iterator& operator=(const Iterator& pOther);

				/**
					@brief Check if two iterators are equal.
					@param pOther iterator to compare current iterator with.
					@return boolean. true if equal. false if not equal.
				*/
				bool operator==(const Iterator& pOther) const;

				/**
					@brief Check if two iterators are not equal.
					@param pOther iterator to compare current iterator with.
					@return boolean. true if not equal. false if equal.
				*/
				bool operator!=(const Iterator& pOther) const;

				/**
					@brief Pre-increment the iterator to point to next item in SList.
					@details If the iterator is pointing to the end of the list, invoking this operator will result in exception being thrown.
					@return Reference to iterator that points to next element in the list.
				*/
				Iterator& operator++();

				/**
					@brief Post-increment the iterator to point to next item in SList.
					@details If the iterator is pointing to the end of the list, invoking this operator will result in exception being thrown.
					@return Reference to current iterator, the invoked iterator will points to next element in the list.
				*/
				Iterator operator++(int32_t);

				/**
					@brief Dereference the iterator to return the data its storing.
					@details If the iterator is pointing to the end of the list, invoking this operator will result in exception being thrown.
					@return Reference to data iterator is holding.
				*/
				T& operator*();

				/**
					@brief Dereference the iterator to return the data its storing.
					@details If the iterator is pointing to the end of the list, invoking this operator will result in exception being thrown.
					@return Reference to data iterator is holding.
				*/
				const T& operator*() const;
			private:
				/**
					@brief Constructor for creating new iterator.
					@param pOwnerList const pointer to the list that owns the iterator.
					@param pCurrentNode Pointer to the node that the iterator is pointing to.
				*/
				Iterator(const SList<T>* pOwnerList, Node* pCurrentNode);

				/**
					Pointer to the owner SList to which this iterator belongs to.
				*/
				const SList* mOwnerList;

				/**
					Pointer to the node that this iterator is pointing to.
				*/
				Node* mNode;
			};

			/**
				@brief Return the iterator that points to the first element in the list.
				@details If the list is empty this will be same as the iterator pointing to the end of the list.
				@return Iterator that points to the first element in the list.
				@see end()
			*/
			Iterator begin() const;

			/**
				@brief Return the iterator that points to the last element in the list.
				@details If the list is empty this will be same as the iterator pointing to the beginning of the list.
				@return Iterator that points to the last element in the list.
				@see begin()
			*/
			Iterator end() const;

		private:
			/**
				Node class is private inner class to SList class. Only SList can create instance of this class.
			*/
			class Node
			{
			public:
				/**
					Pointer to the next node.
				*/
				Node* mNextNode;

				/**
					Data the node is holding.
				*/
				T mData;

				/**
					@brief Constructor that takes data and next node to create a node.
					@param pData The data that this node will be holding.
					@param pNextNode Pointer to the next node.
				*/
				Node(T pData, Node* pNextNode) : mData(pData), mNextNode(pNextNode) {}
			};

			/**
				Pointer that holds the front position of the singly linked list.
			*/
			Node* mFrontNode;

			/**
				Pointer that holds the back position of the singly linked list.
			*/
			Node* mBackNode;

			/**
				Size of the pointer.
				@see Size()
			*/
			std::uint32_t mSize;
		};
	}
}

#include "SList.inl"