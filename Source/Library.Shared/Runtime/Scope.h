#pragma once

#include "RTTI.h"
#include "Datum.h"
#include "Container/Hashmap.h"
#include "Container/Vector.h"

namespace NoobEngine
{
	namespace Runtime
	{
		class Datum;
		
		class Scope : public RTTI
		{
			
		public:
			/**
			 * @brief Scope constructor that takes size as input.
			 * @details The default value of pSize is 0.
			 * @param pSize Size of the scope.
			 */
			Scope(uint32_t pSize = 11);

			/**
			 * @brief Copy constructor for scope
			 * @param pOther The scope that needs to be copied.
			 */
			Scope(const Scope& pOther);

			/**
			 * @brief Destructor
			 */
			virtual ~Scope();

			/**
			 * @brief Search the current scope for the key and if it finds the key returns the datum corresponding to the key or else return nullptr.
			 * @param pKey String that holds the value of the key that needs to be searched for.
			 * @return Datum pointer that points to the datum if key is found, if not found nullptr.
			 * @see Search()
			 */
			Datum* Find(const std::string& pKey) const;

			/**
			 * @brief Search the current scope and all the parent scopes for the key and if found returns the pointer to datum corresponding to the key or else return nullptr.
			 * @param pKey String that holds the value of the key that needs to be searched for.
			 * @param pScope Output variable that will hold the pointer to the scope by the end of call to search().;
			 * @return Datum pointer that points to the datum if key is found, if not found nullptr.
			 * @see Find()
			 */
			Datum* Search(const std::string& pKey, Scope** pScope) const;

			/**
			 * @brief If the key exists it will return the reference associated to the datum that key is pointing to or else creates a default datum is created and inserted.
			 * @param pKey String that holds the value of the key at which datum needs to be appended.
			 * @return Reference to a datum.
			 * @see AppendScope()
			 */
			Datum& Append(const std::string& pKey);

			/**
			 * @brief If the key exists it will add the current scope to the scopes that key is pointing to, else creates a new datum of type scope and insert at key.
			 * @details The created scope will automatically be parented to the scope in which key is found.
			 * @param pKey String that holds the value of the key at which scope needs to be appended.
			 * @return Reference to the scope that is at the location the key is pointing to.
			 * @see Append()
			 * @see operator[]
			 */
			Scope& AppendScope(const std::string& pKey);

			/**
			 * @brief Adopts the child scope as a child and append it at the key. If there are already children at the key, then it will insert at the index provided.
			 * @param pChildToAdopt Reference to scope that should be adopted by this scope.
			 * @param pKey The key at which the child should be associated with.
			 * @param pIndex If there are children at the key specified, this will be the index at which child will be adopted.
			 * @see GetParent()
			 */
			void Adopt(Scope& pChildToAdopt, const std::string& pKey, uint32_t pIndex);

			/**
			 * @brief Returns the pointer to parent.
			 * @return Scope pointer that points to the parent. If there is no parent nullptr is returned.
			 * @see Adopt()
			 */
			Scope* GetParent() const;

			/**
			 * @brief Searches and returns the key associated to the scope.
			 * @param pScope The scope for which the key needs to be found.
			 * @return String that holds the key of the scope.
			 */
			std::string FindName(const Scope& pScope);

			/**
			 * @brief Compare two scopes and return true if they are equal.
			 * @details the RTTI* pointer will be casted to Scope*.
			 * @param pOther RTTI* that needs to be compares. 
			 */
			virtual bool Equals(const RTTI* pOther) const override;

			virtual std::string ToString() const override;

			/**
			 * @brief Assignment operator that does the deep copy of all the elements in pOther into the current scope.
			 * @param pOther The scope variable that needs to be copied.
			 */
			Scope& operator=(const Scope& pOther);

			/**
			 * @brief Return the scope that key is pointing towards. If there is no scope it will create a default scope and return the scope.
			 * @param pKey String that holds the key.
			 * @return Reference to the scope at the key.
			 * @see Append()
			 * @see operator[]
			 */
			Datum& operator[](const std::string& pKey);

			/**
			 * @brief Takes the index and return the reference to the scope that is inserted at that index.
			 * @details The index is calculated as the order in which the scopes are inserted. If the index is bigger than the size it will throw exception.
			 * @param pIndex Unsigned int that holds the index.
			 * @return Reference to the scope at the index.
			 * @see operator[]
			 */
			Datum& operator[](uint32_t pIndex) const;

			/**
			 * @brief Compare the contents of two scopes and return true if they are equal else false.
			 * @param pOther Reference to scope that has to be compared with.
			 * @see operator!=()
			 */
			bool operator==(const Scope& pOther) const;

			/**
			 * @brief Compare the contents of two scopes and return false if they are equal else true.
			 * @param pOther Reference to scope that has to be compared with.
			 * @see operator==()
			 */
			bool operator!=(const Scope& pOther) const;

		private:
			/**
			 * Holds the pointer to the parent.
			 */
			Scope* mParent;

			/**
			 * Stores the data this scope has.
			 */
			Container::Hashmap<std::string, Datum> mData;

			/**
			 * Has the order in which datums are inserted.
			 */
			Container::Vector<std::pair<string, Datum>*> mDataIndexing;

			/**
			 * @brief Clear all the data that the scope is holding
			 */
			void Clear();
		};
	}
}
