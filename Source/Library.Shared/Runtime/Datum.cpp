#include "pch.h"
#include "Datum.h"

namespace NoobEngine
{
	namespace Runtime
	{
		Datum::Datum(uint32_t pInitCapacity) : 
			mSize(0), mCapacity(pInitCapacity), mType(DatumType::UNASSIGNED), mIsExternalData(false), mData()
		{
			// populating the size table
			mTypeSizeTable[0] = sizeof(int32_t);
			mTypeSizeTable[1] = sizeof(float);
			mTypeSizeTable[2] = sizeof(std::string);
			mTypeSizeTable[3] = sizeof(glm::vec4);
			mTypeSizeTable[4] = sizeof(glm::mat4x4);
			mTypeSizeTable[5] = sizeof(RTTI*);
		}

		Datum::Datum(const Datum& pOther) : 
			mSize(0), mCapacity(pOther.mCapacity), mType(pOther.mType), mIsExternalData(pOther.mIsExternalData), mData()
		{
			// populating the size table
			mTypeSizeTable[0] = sizeof(int32_t);
			mTypeSizeTable[1] = sizeof(float);
			mTypeSizeTable[2] = sizeof(std::string);
			mTypeSizeTable[3] = sizeof(glm::vec4);
			mTypeSizeTable[4] = sizeof(glm::mat4x4);
			mTypeSizeTable[5] = sizeof(RTTI*);

			if (pOther.mIsExternalData)
			{
				// shallow copy
				mData.mVoidPtr = pOther.mData.mVoidPtr;
				mSize = pOther.mSize;
			}
			else
			{
				// deep copy
				//mCapacity = pOther.mCapacity;
				for (uint32_t i = 0; i < pOther.mSize; i++)
				{
					switch (mType)
					{
					case NoobEngine::Runtime::DatumType::INTEGER:
						PushBack(pOther.mData.mIntData[i]);
						break;
					case NoobEngine::Runtime::DatumType::FLOAT:
						PushBack(pOther.mData.mFloatData[i]);
						break;
					case NoobEngine::Runtime::DatumType::STRING:
						PushBack(pOther.mData.mStrData[i]);
						break;
					case NoobEngine::Runtime::DatumType::VECTOR_4:
						PushBack(pOther.mData.mVecData[i]);
						break;
					case NoobEngine::Runtime::DatumType::MATRIX_4x4:
						PushBack(pOther.mData.mMatData[i]);
						break;
					case NoobEngine::Runtime::DatumType::RTTI_TYPE:
						PushBack(pOther.mData.mRTTIPtr[i]);
						break;
					default:
						break;
					}
				}
			}
		}

		Datum::Datum(Datum&& pOther)
		{
			for (uint32_t i = 0; i < 6; ++i)
			{
				mTypeSizeTable[i] = pOther.mTypeSizeTable[i];
			}
			
			mType = pOther.mType;
			mSize = pOther.mSize;
			mCapacity = pOther.mCapacity;
			mIsExternalData = pOther.mIsExternalData;
			mData.mVoidPtr = pOther.mData.mVoidPtr;

			pOther.mType = DatumType::UNASSIGNED;
			pOther.mSize = 0;
			pOther.mCapacity = 0;
			pOther.mIsExternalData = true;
			pOther.mData.mVoidPtr = nullptr;
		}

		Datum::~Datum()
		{
			Clear();
			if (!mIsExternalData)
			{
				free(mData.mVoidPtr);
			}
		}

		DatumType Datum::Type() const
		{
			return mType;
		}

		void Datum::SetType(DatumType pDatumType)
		{
			if (mType == DatumType::UNASSIGNED || mType == pDatumType)
			{
				mType = pDatumType;
			}
			else
			{
				throw std::exception("Illegal assignment of type.");
			}
		}

		uint32_t Datum::Size() const
		{
			return mSize;
		}
		
		void Datum::SetSize(uint32_t pSize)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				throw std::exception("Cannot set size on datum whose type is unknown.");
			}

			if (mIsExternalData)
			{
				throw std::exception("Cannot change size of datum that holds external storage.");
			}

			if (pSize > mCapacity)
			{
				mCapacity = pSize;
				// reallocate
				switch (mType)
				{
				case DatumType::INTEGER:
					mData.mIntData = static_cast<int32_t*>(realloc(mData.mIntData, sizeof(int32_t) * mCapacity));
					break;
				case DatumType::FLOAT:
					mData.mFloatData = static_cast<float*>(realloc(mData.mFloatData, sizeof(float) * mCapacity));
					break;
				case DatumType::STRING:
					mData.mStrData = static_cast<std::string*>(realloc(mData.mFloatData, sizeof(std::string) * mCapacity));
					break;
				case DatumType::VECTOR_4:
					mData.mVecData = static_cast<glm::vec4*>(realloc(mData.mFloatData, sizeof(glm::vec4) * mCapacity));
					break;
				case DatumType::MATRIX_4x4:
					mData.mMatData = static_cast<glm::mat4x4*>(realloc(mData.mFloatData, sizeof(glm::mat4x4) * mCapacity));
					break;
				case DatumType::RTTI_TYPE:
					mData.mRTTIPtr = static_cast<RTTI**>(realloc(mData.mFloatData, sizeof(RTTI*) * mCapacity));
					break;
				case DatumType::TABLE:
					mData.mTablePtr = static_cast<Scope**>(realloc(mData.mFloatData, sizeof(Scope*) * mCapacity));
					break;
				default:
					break;
				}
			}
			else
			{
				if (!mIsExternalData)
				{
					// if pSize is less than mCapacity
					for (uint32_t i = pSize; i < mSize; ++i)
					{
						if (mType == DatumType::STRING)
						{
							Destroy(mData.mStrData[i]);
						}
						else if (mType == DatumType::RTTI_TYPE)
						{
							Destroy(mData.mRTTIPtr[i]);
						}
					}
				}
			}

			mSize = pSize;
		}

		void Datum::Clear()
		{
			// only RTTI objects are pointers that means only RTTI objects needs to be deleted.
			if (!mIsExternalData)
			{
				for (uint32_t i = 0; i < mSize; i++)
				{
					if (mType == DatumType::STRING)
					{
						Destroy(mData.mStrData[i]);
					}
					else if (mType == DatumType::RTTI_TYPE)
					{
						Destroy(mData.mRTTIPtr[i]);
					}
				}
			}
			
			mSize = 0;
		}
#pragma region SetStorage
		void Datum::SetStorage(int32_t* pArrayData, uint32_t pSize)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::INTEGER;
			}
			if (mType != DatumType::INTEGER)
			{
				throw std::exception("Unsupported type.");
			}

			Clear();
			if (!mIsExternalData)
			{
				free(mData.mVoidPtr);
			}
			
			mData.mVoidPtr = pArrayData;
			mSize = mCapacity = pSize;
			mIsExternalData = true;
		}

		void Datum::SetStorage(float* pArrayData, uint32_t pSize)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::FLOAT;
			}
			if (mType != DatumType::FLOAT)
			{
				throw std::exception("Unsupported type.");
			}

			Clear();
			if (!mIsExternalData)
			{
				free(mData.mVoidPtr);
			}

			mData.mVoidPtr = pArrayData;
			mSize = mCapacity = pSize;
			mIsExternalData = true;
		}

		void Datum::SetStorage(std::string* pArrayData, uint32_t pSize)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::STRING;
			}
			if (mType != DatumType::STRING)
			{
				throw std::exception("Unsupported type.");
			}

			Clear();
			if (!mIsExternalData)
			{
				free(mData.mVoidPtr);
			}

			mData.mVoidPtr = pArrayData;
			mSize = mCapacity = pSize;
			mIsExternalData = true;
		}

		void Datum::SetStorage(glm::vec4* pArrayData, uint32_t pSize)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::VECTOR_4;
			}
			if (mType != DatumType::VECTOR_4)
			{
				throw std::exception("Unsupported type.");
			}

			Clear();
			if (!mIsExternalData)
			{
				free(mData.mVoidPtr);
			}

			mData.mVoidPtr = pArrayData;
			mSize = mCapacity = pSize;
			mIsExternalData = true;
		}

		void Datum::SetStorage(glm::mat4x4* pArrayData, uint32_t pSize)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::MATRIX_4x4;
			}
			if (mType != DatumType::MATRIX_4x4)
			{
				throw std::exception("Unsupported type.");
			}

			Clear();
			if (!mIsExternalData)
			{
				free(mData.mVoidPtr);
			}

			mData.mVoidPtr = pArrayData;
			mSize = mCapacity = pSize;
			mIsExternalData = true;
		}

		void Datum::SetStorage(RTTI** pArrayData, uint32_t pSize)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::RTTI_TYPE;
			}
			if (mType != DatumType::RTTI_TYPE)
			{
				throw std::exception("Unsupported type.");
			}

			Clear();
			if (!mIsExternalData)
			{
				free(mData.mVoidPtr);
			}

			mData.mVoidPtr = pArrayData;
			mSize = mCapacity = pSize;
			mIsExternalData = true;
		}
#pragma endregion
#pragma region Set
		void Datum::Set(const int32_t& pData, uint32_t pIndex)
		{
			if (mType != DatumType::INTEGER)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (pIndex < mSize)
			{
				mData.mIntData[pIndex] = pData;
			}
			else
			{
				throw std::exception("Index out of bounds. Set<int32_t>");
			}
		}

		void Datum::Set(const float& pData, uint32_t pIndex)
		{
			if (mType != DatumType::FLOAT)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (pIndex < mSize)
			{
				mData.mFloatData[pIndex] = pData;
			}
			else
			{
				throw std::exception("Index out of bounds. Set<float>");
			}
		}

		void Datum::Set(const std::string& pData, uint32_t pIndex)
		{
			if (mType != DatumType::STRING)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (pIndex < mSize)
			{
				mData.mStrData[pIndex] = pData;
			}
			else
			{
				throw std::exception("Index out of bounds. Set<std::string>");
			}
		}

		void Datum::Set(const glm::vec4& pData, uint32_t pIndex)
		{
			if (mType != DatumType::VECTOR_4)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (pIndex < mSize)
			{
				mData.mVecData[pIndex] = pData;
			}
			else
			{
				throw std::exception("Index out of bounds. Set<glm::vec4>");
			}
		}

		void Datum::Set(const glm::mat4x4& pData, uint32_t pIndex)
		{
			if (mType != DatumType::MATRIX_4x4)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (pIndex < mSize)
			{
				mData.mMatData[pIndex] = pData;
			}
			else
			{
				throw std::exception("Index out of bounds. Set<glm::mat4x4>");
			}
		}

		void Datum::Set(RTTI* const& pData, uint32_t pIndex)
		{
			if (mType != DatumType::RTTI_TYPE)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (pIndex < mSize)
			{
				mData.mRTTIPtr[pIndex] = pData;
			}
			else
			{
				throw std::exception("Index out of bounds. Set<RTTI*>");
			}
		}

		void Datum::Set(Scope* const& pData, uint32_t pIndex)
		{
			if (mType != DatumType::TABLE)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (pIndex < mSize)
			{
				mData.mTablePtr[pIndex] = pData;
			}
			else
			{
				throw std::exception("Index out of bounds. Set<Scope*>");
			}
		}
#pragma endregion
#pragma region PushBack
		void Datum::PushBack(const int32_t& pData)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::INTEGER;
			}

			if (mType != DatumType::INTEGER)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (mIsExternalData)
			{
				throw std::exception("Cannot push on datum that holds external data.");
			}

			if (!mData.mVoidPtr)
			{
				// if this is the first element that is being pushed then allocate just enough memory to save one element.
				mData.mIntData = static_cast<int32_t*>(malloc(sizeof(int32_t) * mCapacity));
			}

			if (mSize == mCapacity)
			{
				// Increase the capacity
				mCapacity += 5;
				mData.mIntData = static_cast<int32_t*>(realloc(mData.mIntData, sizeof(int32_t) * mCapacity));
			}

			new (mData.mIntData + mSize++)int32_t(pData);
		}

		void Datum::PushBack(const float& pData)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::FLOAT;
			}
			
			if (mType != DatumType::FLOAT)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (mIsExternalData)
			{
				throw std::exception("Cannot push on datum that holds external data.");
			}

			if (!mData.mVoidPtr)
			{
				// if this is the first element that is being pushed then allocate just enough memory to save one element.
				mData.mFloatData = static_cast<float*>(malloc(sizeof(float) * mCapacity));
			}

			if (mSize == mCapacity)
			{
				// Increase the capacity
				mCapacity += 5;
				mData.mFloatData = static_cast<float*>(realloc(mData.mFloatData, sizeof(float) * mCapacity));
			}

			new (mData.mFloatData + mSize++)float(pData);
		}

		void Datum::PushBack(const std::string& pData)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::STRING;
			}
			
			if (mType != DatumType::STRING)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (mIsExternalData)
			{
				throw std::exception("Cannot push on datum that holds external data.");
			}

			if (!mData.mVoidPtr)
			{
				// if this is the first element that is being pushed then allocate just enough memory to save one element.
				mData.mStrData = static_cast<std::string*>(malloc(sizeof(std::string) * mCapacity));
			}

			if (mSize == mCapacity)
			{
				// Increase the capacity
				mCapacity += 5;
				mData.mStrData = static_cast<std::string*>(realloc(mData.mStrData, sizeof(std::string) * mCapacity));
			}

			new (mData.mStrData + mSize++)std::string(pData);
		}

		void Datum::PushBack(const glm::vec4& pData)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::VECTOR_4;
			}
			
			if (mType != DatumType::VECTOR_4)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (mIsExternalData)
			{
				throw std::exception("Cannot push on datum that holds external data.");
			}

			if (!mData.mVoidPtr)
			{
				// if this is the first element that is being pushed then allocate just enough memory to save one element.
				mData.mVecData = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * mCapacity));
			}

			if (mSize == mCapacity)
			{
				// Increase the capacity
				mCapacity += 5;
				mData.mVecData = static_cast<glm::vec4*>(realloc(mData.mVecData, sizeof(glm::vec4) * mCapacity));
			}

			new (mData.mVecData + mSize++)glm::vec4(pData);
		}

		void Datum::PushBack(const glm::mat4x4& pData)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::MATRIX_4x4;
			}
			
			if (mType != DatumType::MATRIX_4x4)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (mIsExternalData)
			{
				throw std::exception("Cannot push on datum that holds external data.");
			}

			if (!mData.mVoidPtr)
			{
				// if this is the first element that is being pushed then allocate just enough memory to save one element.
				mData.mMatData = static_cast<glm::mat4x4*>(malloc(sizeof(glm::mat4x4) * mCapacity));
			}

			if (mSize == mCapacity)
			{
				// Increase the capacity
				mCapacity += 5;
				mData.mMatData = static_cast<glm::mat4x4*>(realloc(mData.mMatData, sizeof(glm::mat4x4) * mCapacity));
			}

			new (mData.mMatData + mSize++)glm::mat4x4(pData);
		}

		void Datum::PushBack(RTTI* const& pData)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::RTTI_TYPE;
			}
			if (mType != DatumType::RTTI_TYPE)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (mIsExternalData)
			{
				throw std::exception("Cannot push on datum that holds external data.");
			}

			if (!mData.mVoidPtr)
			{
				// if this is the first element that is being pushed then allocate just enough memory to save one element.
				mData.mRTTIPtr = static_cast<RTTI**>(malloc(sizeof(RTTI*) * mCapacity));
			}

			if (mSize == mCapacity)
			{
				// Increase the capacity
				mCapacity += 5;
				mData.mRTTIPtr = static_cast<RTTI**>(realloc(mData.mRTTIPtr, sizeof(RTTI*) * mCapacity));
			}

			new (mData.mRTTIPtr + mSize++)(RTTI*)(const_cast<RTTI*>(pData));
		}

		void Datum::PushBack(Scope* const& pData)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				mType = DatumType::TABLE;
			}
			if (mType != DatumType::TABLE)
			{
				throw std::exception("DatumType doesn't match with the data.");
			}

			if (mIsExternalData)
			{
				throw std::exception("Cannot push on datum that holds external data.");
			}

			if (!mData.mVoidPtr)
			{
				// if this is the first element that is being pushed then allocate just enough memory to save one element.
				mData.mTablePtr = static_cast<Scope**>(malloc(sizeof(Scope*) * mCapacity));
			}

			if (mSize == mCapacity)
			{
				// Increase the capacity
				mCapacity += 5;
				mData.mTablePtr = static_cast<Scope**>(realloc(mData.mTablePtr, sizeof(Scope*) * mCapacity));
			}

			new (mData.mTablePtr + mSize++)(Scope*)(const_cast<Scope*>(pData));
		}
#pragma endregion
		void Datum::PopBack()
		{
			if (mSize == 0)
			{
				throw std::exception("Cannot pop on empty datum.");
			}

			if (!mIsExternalData)
			{
				switch (mType)
				{
				case NoobEngine::Runtime::DatumType::INTEGER:
					Destroy(mData.mIntData[--mSize]);
					break;
				case NoobEngine::Runtime::DatumType::FLOAT:
					Destroy(mData.mFloatData[--mSize]);
					break;
				case NoobEngine::Runtime::DatumType::STRING:
					Destroy(mData.mStrData[--mSize]);
					break;
				case NoobEngine::Runtime::DatumType::VECTOR_4:
					Destroy(mData.mVecData[--mSize]);
					break;
				case NoobEngine::Runtime::DatumType::MATRIX_4x4:
					Destroy(mData.mMatData[--mSize]);
					break;
				case NoobEngine::Runtime::DatumType::RTTI_TYPE:
					Destroy(mData.mRTTIPtr[--mSize]);
					break;
				default:
					break;
				}
			}
			else
			{
				--mSize;
			}
		}

		void Datum::RemoveSafeAt(uint32_t pIndex)
		{
			if(mType == DatumType::UNASSIGNED)
			{
				throw std::exception("Cannot remove from datum who's type is unassigned.");
			}

			if(pIndex >= mSize)
			{
				throw std::exception("Index out of bounds.");
			}

			switch(mType)
			{
			case DatumType::INTEGER:
				memcpy(mData.mIntData + pIndex, mData.mIntData + (pIndex + 1), (mSize - pIndex) * sizeof(int32_t));
				break;
			case DatumType::FLOAT:
				memcpy(mData.mFloatData + pIndex, mData.mFloatData + (pIndex + 1), (mSize - pIndex) * sizeof(float));
				break;
			case DatumType::STRING:
				memcpy(mData.mStrData + pIndex, mData.mStrData + (pIndex + 1), (mSize - pIndex) * sizeof(std::string));
				break;
			case DatumType::VECTOR_4:
				memcpy(mData.mVecData + pIndex, mData.mVecData + (pIndex + 1), (mSize - pIndex) * sizeof(glm::vec4));
				break;
			case DatumType::MATRIX_4x4:
				memcpy(mData.mMatData + pIndex, mData.mMatData + (pIndex + 1), (mSize - pIndex) * sizeof(glm::mat4x4));
				break;
			case DatumType::RTTI_TYPE:
				memcpy(mData.mRTTIPtr + pIndex, mData.mRTTIPtr + (pIndex + 1), (mSize - pIndex) * sizeof(RTTI*));
				break;
			case DatumType::TABLE:
				memcpy(mData.mTablePtr + pIndex, mData.mTablePtr + (pIndex + 1), (mSize - pIndex) * sizeof(Scope*));
				break;
			default:
				break;
			}
			--mSize;
		}

		void Datum::SetFromString(const std::string& pString, uint32_t pIndex)
		{
			if (mType == DatumType::UNASSIGNED)
			{
				throw std::exception("Type needs to set before calling set from string.");
			}

			if (pIndex > mSize)
			{
				throw std::exception("Index out of bounds");
			}

			switch (mType)
			{
			case NoobEngine::Runtime::DatumType::INTEGER:
			{
				int i = std::stoi(pString);
				if (pIndex == mSize)
				{
					//push back
					PushBack(i);
				}
				else
				{
					// set
					Set(i, pIndex);
				}

				break;
			}
			case NoobEngine::Runtime::DatumType::FLOAT:
			{
				float f = std::stof(pString);
				if (pIndex == mSize)
				{
					//push back
					PushBack(f);
				}
				else
				{
					// set
					Set(f, pIndex);
				}

				break;
			}
			case NoobEngine::Runtime::DatumType::STRING:
				if (pIndex == mSize)
				{
					//push back
					PushBack(pString);
				}
				else
				{
					// set
					Set(pString, pIndex);
				}
				
				break;
			case NoobEngine::Runtime::DatumType::VECTOR_4:
			{
				//expected format {x, y, z, w}
				glm::vec4 tmpVec;
				sscanf(pString.c_str(),
					"{%f, %f, %f, %f}",
					&tmpVec.x, &tmpVec.y, &tmpVec.z, &tmpVec.w);

				if (pIndex == mSize)
				{
					//push back
					PushBack(tmpVec);
				}
				else
				{
					// set
					Set(tmpVec, pIndex);
				}

				break;
			}
			case NoobEngine::Runtime::DatumType::MATRIX_4x4:
			{
				// expected format 
				// {c0r0, c0r1, c0r2, c0r3}, {c1r0, c1r1, c1r2, c1r3}, {c2r0, c2r1, c2r2, c2r3}, {c3r0, c3r1, c3r2, c3r3}
				glm::mat4x4 tmpMat;
				sscanf(pString.c_str(), 
					"{{%f, %f, %f, %f}, {%f, %f, %f, %f}, {%f, %f, %f, %f}, {%f, %f, %f, %f}}",
					&tmpMat[0].x, &tmpMat[0].y, &tmpMat[0].z, &tmpMat[0].w, 
					&tmpMat[1].x, &tmpMat[1].y, &tmpMat[1].z, &tmpMat[1].w,
					&tmpMat[2].x, &tmpMat[2].y, &tmpMat[2].z, &tmpMat[2].w, 
					&tmpMat[3].x, &tmpMat[3].y, &tmpMat[3].z, &tmpMat[3].w);


				if (pIndex == mSize)
				{
					//push back
					PushBack(tmpMat);
				}
				else
				{
					// set
					Set(tmpMat, pIndex);
				}

				break;
			}
			case NoobEngine::Runtime::DatumType::RTTI_TYPE:
				break;
			default:
				break;
			}
		}

		std::string Datum::ToString(uint32_t pIndex) const
		{
			if (pIndex >= mSize)
			{
				throw std::exception("Index out of bounds");
			}
			
			std::ostringstream stringStream;
			std::string resultStr;

			switch (mType)
			{
			case NoobEngine::Runtime::DatumType::INTEGER:
				stringStream << Get<int32_t>(pIndex);
				resultStr = stringStream.str();

				break;
			case NoobEngine::Runtime::DatumType::FLOAT:
				stringStream << Get<float>(pIndex);
				resultStr = stringStream.str();

				break;
			case NoobEngine::Runtime::DatumType::STRING:
				resultStr = Get<std::string>(pIndex);
				
				break;
			case NoobEngine::Runtime::DatumType::VECTOR_4:
			{
				glm::vec4 tmpVec = Get<glm::vec4>(pIndex);
				stringStream << "{" << tmpVec.x << ", " << tmpVec.y << ", " << tmpVec.z << ", " << tmpVec.w << "}";
				resultStr = stringStream.str();

				break;
			}
			case NoobEngine::Runtime::DatumType::MATRIX_4x4:
			{
				glm::mat4x4 tmpMat = Get<glm::mat4x4>(pIndex);
				stringStream << "{"
					<< "{" << tmpMat[0].x << ", " << tmpMat[0].y << ", " << tmpMat[0].z << ", " << tmpMat[0].w << "}, "
					<< "{" << tmpMat[1].x << ", " << tmpMat[1].y << ", " << tmpMat[1].z << ", " << tmpMat[1].w << "}, "
					<< "{" << tmpMat[2].x << ", " << tmpMat[2].y << ", " << tmpMat[2].z << ", " << tmpMat[2].w << "}, "
					<< "{" << tmpMat[3].x << ", " << tmpMat[3].y << ", " << tmpMat[3].z << ", " << tmpMat[3].w << "}"
					<< "}";
				resultStr = stringStream.str();

				break;
			}
			case NoobEngine::Runtime::DatumType::RTTI_TYPE:
				resultStr = Get<RTTI*>(pIndex)->ToString();
				break;
			default:
				break;
			}
			
			return resultStr;
		}
#pragma region AssignmentOperator
		Datum& Datum::operator=(const Datum& pOther)
		{
			if (this != &pOther)
			{
				Clear();
				mType = pOther.mType;

				// handling data
				if (pOther.mIsExternalData)
				{
					// do shallow copy
					if (!mIsExternalData)
					{
						// free memory only if data is internal
						free(mData.mVoidPtr);
					}

					mData = pOther.mData;
					mSize = pOther.mSize;
					mCapacity = pOther.mCapacity;
				}
				else
				{
					// internal memory
					// do deep copy
					for (uint32_t i = 0; i < pOther.mSize; ++i)
					{
						switch (mType)
						{
						case DatumType::INTEGER:
							PushBack(pOther.mData.mIntData[i]);
							break;
						case DatumType::FLOAT:
							PushBack(pOther.mData.mFloatData[i]);
							break;
						case DatumType::STRING:
							PushBack(pOther.mData.mStrData[i]);
							break;
						case DatumType::VECTOR_4:
							PushBack(pOther.mData.mVecData[i]);
							break;
						case DatumType::MATRIX_4x4:
							PushBack(pOther.mData.mMatData[i]);
							break;
						case DatumType::RTTI_TYPE:
							PushBack(pOther.mData.mRTTIPtr[i]);
							break;
						case DatumType::TABLE:
							PushBack(pOther.mData.mTablePtr[i]);
							break;
						default:
							break;
						}
					}
				}
				
				mIsExternalData = pOther.mIsExternalData;
			}
			
			return *this;
		}

		Datum& Datum::operator=(Datum&& pOther)
		{
			if (this != &pOther)
			{
				Clear();
				for (uint32_t i = 0; i < 6; ++i)
				{
					mTypeSizeTable[i] = pOther.mTypeSizeTable[i];
				}

				mType = pOther.mType;
				mSize = pOther.mSize;
				mCapacity = pOther.mCapacity;
				mIsExternalData = pOther.mIsExternalData;
				mData.mVoidPtr = pOther.mData.mVoidPtr;

				pOther.mType = DatumType::UNASSIGNED;
				pOther.mSize = 0;
				pOther.mCapacity = 0;
				pOther.mIsExternalData = true;
				pOther.mData.mVoidPtr = nullptr;
			}

			return *this;
		}

		Datum& Datum::operator=(const int32_t& pOther)
		{
			if (mType != DatumType::UNASSIGNED && mType != DatumType::INTEGER)
			{
				throw std::exception("Datum type is not int type.");
			}

			if (mSize == 0)
			{
				PushBack(pOther);
			}
			else
			{
				Set(pOther);
			}
			return *this;
		}

		Datum& Datum::operator=(const float & pOther)
		{
			if (mType != DatumType::UNASSIGNED && mType != DatumType::FLOAT)
			{
				throw std::exception("Datum type is not float type.");
			}

			if (mSize == 0)
			{
				PushBack(pOther);
			}
			else
			{
				Set(pOther);
			}
			return *this;
		}

		Datum& Datum::operator=(const std::string & pOther)
		{
			if (mType != DatumType::UNASSIGNED && mType != DatumType::STRING)
			{
				throw std::exception("Datum type is not string type.");
			}

			if (mSize == 0)
			{
				PushBack(pOther);
			}
			else
			{
				Set(pOther);
			}
			return *this;
		}

		Datum& Datum::operator=(const glm::vec4 & pOther)
		{
			if (mType != DatumType::UNASSIGNED && mType != DatumType::VECTOR_4)
			{
				throw std::exception("Datum type is not glm::vec4 type.");
			}

			if (mSize == 0)
			{
				PushBack(pOther);
			}
			else
			{
				Set(pOther);
			}
			return *this;
		}

		Datum& Datum::operator=(const glm::mat4x4 & pOther)
		{
			if (mType != DatumType::UNASSIGNED && mType != DatumType::MATRIX_4x4)
			{
				throw std::exception("Datum type is not glm::mat4x4 type.");
			}

			if (mSize == 0)
			{
				PushBack(pOther);
			}
			else
			{
				Set(pOther);
			}
			return *this;
		}

		Datum& Datum::operator=(RTTI* const& pOther)
		{
			if (mType != DatumType::UNASSIGNED && mType != DatumType::RTTI_TYPE)
			{
				throw std::exception("Datum type is not RTTI* type.");
			}

			if (mSize == 0)
			{
				PushBack(pOther);
			}
			else
			{
				Set(const_cast<RTTI*>(pOther));
			}
			return *this;
		}

		Datum& Datum::operator=(Scope* const& pOther)
		{
			if (mType != DatumType::UNASSIGNED && mType != DatumType::TABLE)
			{
				throw std::exception("Datum type is not Scope* type.");
			}

			if (mSize == 0)
			{
				PushBack(pOther);
			}
			else
			{
				Set(const_cast<Scope*>(pOther));
			}
			return *this;
		}
#pragma endregion
#pragma region ComparisonOperator
		bool Datum::operator==(const Datum& pOther) const
		{
			if (this == &pOther)
			{
				return true;
			}

			if (mType != pOther.mType || mSize != pOther.mSize)
			{
				return false;
			}

			if (mSize > 0)
			{
				// comparing memory will work only for basic data types and classes that doesn't have pointers as members.
				if (mType == DatumType::STRING)
				{
					for (uint32_t i = 0; i < mSize; i++)
					{
						if (mData.mStrData[i] != pOther.mData.mStrData[i])
						{
							return false;
						}
					}
				}
				else if (mType == DatumType::RTTI_TYPE || mType == DatumType::TABLE)
				{
					for (uint32_t i = 0; i < mSize; i++)
					{
						if (mData.mRTTIPtr[i] && pOther.mData.mRTTIPtr[i] && !mData.mRTTIPtr[i]->Equals(pOther.mData.mRTTIPtr[i]))
						{
							return false;
						}
					}
				}
				else
				{
					// compare the memory blocks 
					int result = memcmp(mData.mVoidPtr, pOther.mData.mVoidPtr, mSize * mTypeSizeTable[static_cast<uint32_t>(mType)]);
					return (result == 0);
				}
			}
			
			return true;
		}

		bool Datum::operator!=(const Datum& pOther) const
		{
			return !(operator==(pOther));
		}

		Scope*& Datum::operator[](uint32_t pIndex)
		{
			return Get<Scope*>(pIndex);
		}
#pragma endregion
	}
}