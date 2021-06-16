//
// Created by cbihan on 17/06/2021.
//

#include <algorithm>
#include <cctype>
#include <locale>
#include <string>
#include "Utils.hpp"

namespace BBM
{
	inline void Utils::lTrim(std::string &s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
		}));
	}

	inline void Utils::rTrim(std::string &s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	inline void Utils::trim(std::string &s)
	{
		lTrim(s);
		rTrim(s);
	}

	inline std::string Utils::lTrimCopy(std::string s)
	{
		lTrim(s);
		return s;
	}

	inline std::string Utils::rTrimCopy(std::string s)
	{
		rTrim(s);
		return s;
	}

	inline std::string Utils::trimCopy(std::string s)
	{
		trim(s);
		return s;
	}

}