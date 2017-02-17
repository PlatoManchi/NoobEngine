#pragma once
namespace NoobEngine
{
	namespace Runtime
	{
		template<typename T>
		T& Datum::Get(uint32_t pIndex)
		{
			pIndex;
			throw std::exception("Invalid type.");
		}

		template<typename T>
		const T& Datum::Get(uint32_t pIndex) const
		{
			pIndex;
			throw std::exception("Invalid type.");
		}

		template<>
		int32_t& Datum::Get<int32_t>(uint32_t pIndex)
		{
			if (pIndex < mSize)
			{
				return mData.mIntData[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<int32_t>");
			}
		}

		template<>
		const int32_t& Datum::Get<int32_t>(uint32_t pIndex) const
		{
			if (pIndex < mSize)
			{
				return mData.mIntData[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<int32_t>");
			}
		}

		template<>
		float& Datum::Get<float>(uint32_t pIndex)
		{
			if (pIndex < mSize)
			{
				return mData.mFloatData[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<float>");
			}
		}

		template<>
		const float& Datum::Get<float>(uint32_t pIndex) const
		{
			if (pIndex < mSize)
			{
				return mData.mFloatData[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<float>");
			}
		}

		template<>
		std::string& Datum::Get<std::string>(uint32_t pIndex)
		{
			if (pIndex < mSize)
			{
				return mData.mStrData[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<std::string>");
			}
		}

		template<>
		const std::string& Datum::Get<std::string>(uint32_t pIndex) const
		{
			if (pIndex < mSize)
			{
				return mData.mStrData[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<std::string>");
			}
		}

		template<>
		glm::vec4& Datum::Get<glm::vec4>(uint32_t pIndex)
		{
			if (pIndex < mSize)
			{
				return mData.mVecData[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<glm::vec4>");
			}
		}

		template<>
		const glm::vec4& Datum::Get<glm::vec4>(uint32_t pIndex) const
		{
			if (pIndex < mSize)
			{
				return mData.mVecData[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<glm::vec4>");
			}
		}

		template<>
		glm::mat4x4& Datum::Get<glm::mat4x4>(uint32_t pIndex)
		{
			if (pIndex < mSize)
			{
				return mData.mMatData[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<glm::mat4x4>");
			}
		}

		template<>
		const glm::mat4x4& Datum::Get<glm::mat4x4>(uint32_t pIndex) const
		{
			if (pIndex < mSize)
			{
				return mData.mMatData[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<glm::mat4x4>");
			}
		}

		template<>
		RTTI*& Datum::Get<RTTI*>(uint32_t pIndex)
		{
			if (pIndex < mSize)
			{
				return mData.mRTTIPtr[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<RTTI*>");
			}
		}

		template<>
		RTTI* const& Datum::Get<RTTI*>(uint32_t pIndex) const
		{
			if (pIndex < mSize)
			{
				return mData.mRTTIPtr[pIndex];
			}
			else
			{
				throw std::exception("Index out of bounds. Get<RTTI*>");
			}
		}

		template<typename T>
		void Datum::Destroy(T& pObject)
		{
			pObject;
			pObject.~T();
		}
	}
}
