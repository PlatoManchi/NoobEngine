#pragma once

namespace FIEAGameEngine::Container
{
	/**
		Single linked list is a type of container that can act as dynamic array.
	*/
	class SList
	{
	public:
		SList();
		SList(int32_t pData);

		/**
			Return the data stored in the list
			Const and non-const versions of functions available
		*/
		int32_t GetData();
		int32_t GetData() const;
		
	private:
		int32_t mData;
	};
}