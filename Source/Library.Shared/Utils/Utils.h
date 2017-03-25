#pragma once

namespace NoobEngine
{
	namespace Utils
	{
		/**
			@brief Compare two strings ignoring case
			@param[in] pParam1 First string
			@param[in] pParam2 Second string
			@return True if both strings are equal.
		*/
		bool StrNCaseCmp(std::string pParam1, std::string pParam2);


		/**
			@brief Convert the string to lowercase string.
			@param[in] pString String that needs to be converted to lowercase.
			@return String that was converted to lowercase.
		*/
		std::string ToLower(const std::string& pString);
	}
}