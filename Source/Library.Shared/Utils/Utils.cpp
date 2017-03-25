#include "pch.h"
#include "Utils.h"

namespace NoobEngine
{
	namespace Utils
	{
		bool StrNCaseCmp(std::string pParam1, std::string pParam2) 
		{
			if (pParam1.length() == pParam2.length())
			{
				return std::equal(
					pParam2.begin(), pParam2.end(),
					pParam1.begin(),
					[](unsigned char a, unsigned char b) { return ::tolower(a) == ::tolower(b); }
				);
			}
			return false;
		}

		std::string ToLower(const std::string& pString)
		{
			std::string result;

			for (std::string::size_type i = 0; i < pString.length(); i++)
			{
				result += static_cast<char>(::tolower(pString[i]));
			}
			return result;
		}
	}
}