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
	inline void Utils::ltrim(std::string &s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
		}));
	}

	inline void Utils::rtrim(std::string &s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	inline void Utils::trim(std::string &s)
	{
		ltrim(s);
		rtrim(s);
	}

	inline std::string Utils::ltrim_copy(std::string s)
	{
		ltrim(s);
		return s;
	}

	inline std::string Utils::rtrim_copy(std::string s)
	{
		rtrim(s);
		return s;
	}

	inline std::string Utils::trim_copy(std::string s)
	{
		trim(s);
		return s;
	}

}