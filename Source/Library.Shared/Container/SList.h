#pragma once
#include "pch.h"
namespace FIEAGameEngine::Container
{
	/**
		SList is dynamic sized container class that implements singly linked list
	*/
	template <class T>
	class SList
	{
	public:
		/**
			Create a empty singly list.
		*/
		SList();

		/**
			Deep copy all elements from reference object into new list
		*/
		SList(const SList& pList);

		/**
			Deep copy all elements from the pList into new list object
		*/
		SList(const SList* pList);

		/**
			Standard destructor.
		*/
		~SList();

		/**
			Overloading = to do a deep copy of all the list elements into new list
		*/
		SList& operator=(const SList& pList);

		/**
			Insert the data at front of the list
		*/
		void PushFront(const T& pData);

		/**
			Append data at end of the list
		*/
		void PushBack(const T& pData);


		/**
			Pop the first element of the list.
			
			Throws exception if list is empty
		*/
		T PopFront();

		/**
			Return reference to the first element in the list.
			Changing the value of reference will effect the actual value in the list

			Throws exception if called on empty list
		*/
		T& Front();

		/**
			Return reference to the first element in the list.

			Throws exception if called on empty list
		*/
		T& Front() const;

		/**
			@return Return reference to the last element in the list.
			Changing the value of reference will effect the actual value in the list

			Throws exception if called on empty list
		*/
		T& Back();

		/**
			Throws exception if called on empty list

			Return reference to the last element in the list.
		*/
		T& Back() const;

		/**
			Remove all the elements from list.
		*/
		void Clear();

		/**
			Return the size of the list
		*/
		std::uint32_t Size() const;

		/**
			Returns if the list is empty or not
		*/
		bool IsEmpty() const;

	private:
		/**
			Node class is private inner class to SList class. Only SList can create instance of this class.
		*/
		class Node
		{
		public:
			Node* mNextNode;
			T mData;

			Node() : mNextNode(nullptr) {}
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
			Use Size() method to access the size of list.
		*/
		std::uint32_t mSize;
	};
}

#include "SList.inl"