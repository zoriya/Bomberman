//
// Created by cbihan on 17/06/2021.
//

#include <algorithm>
#include <cctype>
#include <locale>
#include <string>
#include <regex>
#include <ios>
#include <sstream>
#include "Utils.hpp"

namespace BBM
{
	void Utils::lTrim(std::string &s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
		}));
	}

	void Utils::rTrim(std::string &s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	void Utils::trim(std::string &s)
	{
		lTrim(s);
		rTrim(s);
	}

	std::string Utils::lTrimCopy(std::string s)
	{
		lTrim(s);
		return s;
	}

	std::string Utils::rTrimCopy(std::string s)
	{
		rTrim(s);
		return s;
	}

	std::string Utils::trimCopy(std::string s)
	{
		trim(s);
		return s;
	}

	int Utils::findFrequency(const std::string &s, const std::string &pattern)
	{
		std::regex c(pattern);
		std::smatch m;

		ptrdiff_t numberOfMatches = std::distance(std::sregex_iterator(s.begin(), s.end(), c), std::sregex_iterator());
		return static_cast<int>(numberOfMatches);
	}

	std::vector<std::string> Utils::splitStr(const std::string &str, char delim)
	{
		std::vector<std::string> strings;
		std::istringstream f(str);
		std::string buffer;

		while (std::getline(f, buffer, delim)) {;
			strings.push_back(buffer);
		}
		if (str.back() == delim) {
			strings.emplace_back("");
		}
		return strings;
	}
}