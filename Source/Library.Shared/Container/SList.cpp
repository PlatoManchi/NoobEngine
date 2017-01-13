#include "pch.h"
#include "SList.h"

namespace FIEAGameEngine::Container
{
	SList::SList() :mData(0) {}
	SList::SList(int32_t pData) : mData(pData) {}

	int32_t SList::GetData()
	{
		return this->mData;
	}

	int32_t SList::GetData() const
	{
		return this->mData;
	}
}