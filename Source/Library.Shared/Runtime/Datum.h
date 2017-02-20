#pragma once
#include "pch.h"
#include "RTTI.h"
#define GLM_FORCE_CXX98
#include "../../External/glm/glm/vec4.hpp"
#include "../../External/glm/glm/mat4x4.hpp"
//#include "Scope.h"

namespace NoobEngine
{
	namespace Runtime
	{
		class Scope;

		enum class DatumType
		{
			INTEGER = 0, FLOAT = 1, STRING = 2, VECTOR_4 = 3, MATRIX_4x4 = 4, RTTI_TYPE = 5, TABLE = 6, UNASSIGNED
		};

		class Datum final
		{
		public:
			/**
				@brief Default constructor.
			*/
			Datum();

			/**
				@brief Copy constructor
			*/
			Datum(const Datum& pOther);

			/**
				@brief Destructor
			*/
			~Datum();

			/**
				@brief Returns the type this datum is associated with.
				@return DatumType enum object that holds the type of data this datum is holding.
			*/
			DatumType Type() const;

			/**
				@brief Sets the type of datum to the type that is sent as parameter.
				@details If the type is already set and the type provided is not same as the type that is set, the type of the datum will remain same as the previously assigned type.
				@param pDatumType Object of DatumType that holds type of this datum type to be set;
			*/
			void SetType(DatumType pDatumType);

			/**
				@brief Returns the number of elements in the datum.
				@return Unsigned int that holds the size of the datum.
			*/
			uint32_t Size() const;

			/**
				@brief Set the number of elements that can be stored in this datum.
				@details If pSize is less than the capacity then remove all the overflowing elements from datum but keep the capacity same. For example if there are 5 elements in datum and the capacity of the datum is 10, calling SetSize(3) will delete the last two elements from datum and size of datum will become 3 but the capacity of the datum will still remain 10.
				@param pSize Unsigned int that holds the size datum should be.
			*/
			void SetSize(uint32_t pSize);

			/**
				@brief Clear all the elements in the datum without shrinking the capacity of the datum.
			*/
			void Clear();

			/**
				@brief Assign the storage of current datum to the values that are passed in array.
				@param pArrayData Pointer to the data that needs to be set as storage for this datum.
				@param pSize Unsigned int that holds the size of the array that is passed.
			*/
			void SetStorage(int32_t* pArrayData, uint32_t pSize);

			/**
				@brief Assign the storage of current datum to the values that are passed in array.
				@param pArrayData Pointer to the data that needs to be set as storage for this datum.
				@param pSize Unsigned int that holds the size of the array that is passed.
			*/
			void SetStorage(float* pArrayData, uint32_t pSize);

			/**
				@brief Assign the storage of current datum to the values that are passed in array.
				@param pArrayData Pointer to the data that needs to be set as storage for this datum.
				@param pSize Unsigned int that holds the size of the array that is passed.
			*/
			void SetStorage(std::string* pArrayData, uint32_t pSize);

			/**
				@brief Assign the storage of current datum to the values that are passed in array.
				@param pArrayData Pointer to the data that needs to be set as storage for this datum.
				@param pSize Unsigned int that holds the size of the array that is passed.
			*/
			void SetStorage(glm::vec4* pArrayData, uint32_t pSize);

			/**
				@brief Assign the storage of current datum to the values that are passed in array.
				@param pArrayData Pointer to the data that needs to be set as storage for this datum.
				@param pSize Unsigned int that holds the size of the array that is passed.
			*/
			void SetStorage(glm::mat4x4* pArrayData, uint32_t pSize);

			/**
				@brief Assign the storage of current datum to the values that are passed in array.
				@param pArrayData Pointer to the data that needs to be set as storage for this datum.
				@param pSize Unsigned int that holds the size of the array that is passed.
			*/
			void SetStorage(RTTI** pArrayData, uint32_t pSize);

			/**
				@brief Assigns the appropriate index with the value passed.
				@details The default value of index will be 0.
				@param pData Integer data that needs to stored.
				@param pIndex The index at which the data needs to be inserted. Default value of index is 0. pIndex has to be in range of size.
				@see PushBack()
				@see Size()
			*/
			void Set(const int32_t& pData, uint32_t pIndex = 0);

			/**
				@brief Assigns the appropriate index with the value passed.
				@details The default value of index will be 0.
				@param pData Float data that needs to stored.
				@param pIndex The index at which the data needs to be inserted. Default value of index is 0. pIndex has to be in range of size.
				@see PushBack()
				@see Size()
			*/
			void Set(const float& pData, uint32_t pIndex = 0);

			/**
				@brief Assigns the appropriate index with the value passed.
				@details The default value of index will be 0.
				@param pData String data that needs to stored.
				@param pIndex The index at which the data needs to be inserted. Default value of index is 0. pIndex has to be in range of size.
				@see PushBack()
				@see Size()
			*/
			void Set(const std::string& pData, uint32_t pIndex = 0);

			/**
				@brief Assigns the appropriate index with the value passed.
				@details The default value of index will be 0.
				@param pData glm::Vec4 data that needs to stored.
				@param pIndex The index at which the data needs to be inserted. Default value of index is 0. pIndex has to be in range of size.
				@see PushBack()
				@see Size()
			*/
			void Set(const glm::vec4& pData, uint32_t pIndex = 0);

			/**
				@brief Assigns the appropriate index with the value passed.
				@details The default value of index will be 0.
				@param pData glm::mat4x4 data that needs to stored.
				@param pIndex The index at which the data needs to be inserted. Default value of index is 0. pIndex has to be in range of size.
				@see PushBack()
				@see Size()
			*/
			void Set(const glm::mat4x4& pData, uint32_t pIndex = 0);

			/**
				@brief Assigns the appropriate index with the value passed.
				@details The default value of index will be 0.
				@param pData RTTI pointer that needs to stored.
				@param pIndex The index at which the data needs to be inserted. Default value of index is 0. pIndex has to be in range of size.
				@see PushBack()
				@see Size()
			*/
			void Set(RTTI* const& pData, uint32_t pIndex = 0);

			/**
				@brief Assigns the appropriate index with the value passed.
				@details The default value of index will be 0.
				@param pData RTTI pointer that needs to stored.
				@param pIndex The index at which the data needs to be inserted. Default value of index is 0. pIndex has to be in range of size.
				@see PushBack()
				@see Size()
			*/
			void Set(Scope* const& pData, uint32_t pIndex = 0);

			/**
				@brief Push the data at the end of the datum.
				@details PushBack can increase the capacity of the datum if necessary.
				@param pData Data that needs to be pushed.
			*/
			void PushBack(const int32_t& pData);

			/**
				@brief Push the data at the end of the datum.
				@details PushBack can increase the capacity of the datum if necessary.
				@param pData Data that needs to be pushed.
			*/
			void PushBack(const float& pData);

			/**
				@brief Push the data at the end of the datum.
				@details PushBack can increase the capacity of the datum if necessary.
				@param pData Data that needs to be pushed.
			*/
			void PushBack(const std::string& pData);

			/**
				@brief Push the data at the end of the datum.
				@details PushBack can increase the capacity of the datum if necessary.
				@param pData Data that needs to be pushed.
			*/
			void PushBack(const glm::vec4& pData);

			/**
				@brief Push the data at the end of the datum.
				@details PushBack can increase the capacity of the datum if necessary.
				@param pData Data that needs to be pushed.
			*/
			void PushBack(const glm::mat4x4& pData);

			/**
				@brief Push the data at the end of the datum.
				@details PushBack can increase the capacity of the datum if necessary.
				@param pData Data that needs to be pushed.
			*/
			void PushBack(RTTI* const& pData);

			/**
				@brief Push the data at the end of the datum.
				@details PushBack can increase the capacity of the datum if necessary.
				@param pData Data that needs to be pushed.
			*/
			void PushBack(Scope* const& pData);

			/**
				@brief Remove last element from the datum.
			*/
			void PopBack();

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0. Throws exception if the type is not supported.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Reference to the value at pIndex
			*/
			template<typename T>
			T& Get(uint32_t pIndex = 0);

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0. Throws exception if the type is not supported.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Constant reference to the value at pIndex
			*/
			template<typename T>
			const T& Get(uint32_t pIndex = 0) const;

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Reference to int at pIndex
			*/
			template<>
			int32_t& Get<int32_t>(uint32_t pIndex);

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Constant reference to int at pIndex
			*/
			template<>
			const int32_t& Get<int32_t>(uint32_t pIndex) const;

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Reference to float at pIndex
			*/
			template<>
			float& Get<float>(uint32_t pIndex);

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Constant reference to float at pIndex
			*/
			template<>
			const float& Get<float>(uint32_t pIndex) const;

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Reference to string at pIndex
			*/
			template<>
			std::string& Get<std::string>(uint32_t pIndex);

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Constant reference to string at pIndex
			*/
			template<>
			const std::string& Get<std::string>(uint32_t pIndex) const;

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Reference to vec4 at pIndex
			*/
			template<>
			glm::vec4& Get<glm::vec4>(uint32_t pIndex);

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Constant reference to vec4 at pIndex
			*/
			template<>
			const glm::vec4& Get<glm::vec4>(uint32_t pIndex) const;

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Reference to mat4x4 at pIndex
			*/
			template<>
			glm::mat4x4& Get<glm::mat4x4>(uint32_t pIndex);

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Constant reference to mat4x4 at pIndex
			*/
			template<>
			const glm::mat4x4& Get<glm::mat4x4>(uint32_t pIndex) const;

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Reference to RTTI* at pIndex
			*/
			template<>
			RTTI*& Get<RTTI*>(uint32_t pIndex);

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Constant reference to RTTI* at pIndex
			*/
			template<>
			RTTI* const& Get<RTTI*>(uint32_t pIndex) const;

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Reference to RTTI* at pIndex
			*/
			template<>
			Scope*& Get<Scope*>(uint32_t pIndex);

			/**
				@brief Returns the data stored in datum at the index.
				@details The default value of pIndex is 0.
				@param pIndex The index at which the data needs to be retrieved from.
				@return Constant reference to Scope* at pIndex
			*/
			template<>
			Scope* const& Get<Scope*>(uint32_t pIndex) const;

			/**
			 * @brief Remove the element at the index from the datum
			 * @details The destructor will not be called on the elements.
			 * @param pIndex Index at which element shoudl be removed
			 */
			void RemoveSafeAt(uint32_t pIndex);

			/**
				@brief Set the value that is represented by pString at the index given
				@details Default value of pIndex is 0. The function manipulate and change pString, so it is taking a copy of pString instead of reference.
				@param pString std::string that contains the stringified value of the data.
				@param pIndex Unsigned int that holds the index at which this value should be inserted into.
			*/
			void SetFromString(std::string pString, uint32_t pIndex = 0);

			/**
				@brief Returns stringified value of the data at index.
				@details Default value of pIndex is 0.
				@param pIndex Unsigned int that holds the index at which the stringified value should be returned.
			*/
			std::string ToString(uint32_t pIndex = 0) const;

			//-------------------------- Operators ------------------------------
			/**
				@brief Assign the pOther data into this datum.
				@param pOther Datum that needs to be copied.
				@return Reference to datum
			*/
			Datum& operator=(const Datum& pOther);

			/**
				@brief Assign the pOther data into this datum.
				@details This is a scalar assignment. All the elements in the datum will be cleared and the 0th element will be set to the value.
				@param pOther int that needs to be copied.
				@return Reference to datum
			*/
			Datum& operator=(const int32_t& pOther);

			/**
				@brief Assign the pOther data into this datum.
				@details This is a scalar assignment. All the elements in the datum will be cleared and the 0th element will be set to the value.
				@param pOther float that needs to be copied.
				@return Reference to datum
			*/
			Datum& operator=(const float& pOther);

			/**
				@brief Assign the pOther data into this datum.
				@details This is a scalar assignment. All the elements in the datum will be cleared and the 0th element will be set to the value.
				@param pOther string that needs to be copied.
				@return Reference to datum
			*/
			Datum& operator=(const std::string& pOther);

			/**
				@brief Assign the pOther data into this datum.
				@details This is a scalar assignment. All the elements in the datum will be cleared and the 0th element will be set to the value.
				@param pOther glm::vec4 that needs to be copied.
				@return Reference to datum
			*/
			Datum& operator=(const glm::vec4& pOther);

			/**
				@brief Assign the pOther data into this datum.
				@details This is a scalar assignment. All the elements in the datum will be cleared and the 0th element will be set to the value.
				@param pOther glm::mat4x4 that needs to be copied.
				@return Reference to datum
			*/
			Datum& operator=(const glm::mat4x4& pOther);

			/**
				@brief Assign the pOther data into this datum.
				@details This is a scalar assignment. All the elements in the datum will be cleared and the 0th element will be set to the value.
				@param pOther RTTI* that needs to be copied.
				@return Reference to datum
			*/
			Datum& operator=(RTTI* const& pOther);

			/**
				@brief Check if two datums are equal are not.
				@return boolean. true if equal or false.
			*/
			bool operator==(const Datum& pOther);

			/**
				@brief Check if two datums are not equal.
				@return boolean. true if not equal or false.
			*/
			bool operator!=(const Datum& pOther);
		private:
			/**
				Union to hold the pointer to the location where datum data is stored.
			*/
			union DatumValue
			{
				void* mVoidPtr;
				int32_t* mIntData;
				float* mFloatData;
				std::string* mStrData;
				glm::vec4* mVecData;
				glm::mat4x4* mMatData;
				RTTI** mRTTIPtr;
				Scope** mTablePtr;
			};

			/**
				Holds the type of this datum.
			*/
			DatumType mType;

			/**
				Stores the array of datum data.
			*/
			DatumValue mData;

			/**
				If true that means that the data is not owned by this datum.
			*/
			bool mIsExternalData;

			/**
				Number of elements that datum contains.
			*/
			uint32_t mSize;

			/**
				The total capacity of this datum
			*/
			uint32_t mCapacity;

			/**
				Table that holds the sizes of all supported types
			*/
			uint32_t mTypeSizeTable[6];

			/**
				@brief Calls destructor on the object.
				@param pObject Reference to the object on which destructor will be called.
			*/
			template <typename T>
			void Destroy(T& pObject);
		};
	}
}

#include "Datum.inl"