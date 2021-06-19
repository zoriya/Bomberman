//
// Created by cbihan on 17/06/2021.
//

#pragma once

namespace BBM
{
	struct Utils
	{
		//! @brief trim left end
		static void lTrim(std::string &s);

		//! @brief trim right end
		static void rTrim(std::string &s);

		//! @brief trim from both ends
		static void trim(std::string &s);

		//! @brief trim left end (copying)
		static std::string lTrimCopy(std::string s);

		//! @brief trim right end (copying)
		static std::string rTrimCopy(std::string s);

		//! @brief trim from both ends (copying)
		static std::string trimCopy(std::string s);

		//! @brief find the frequency of a substring in a string
		static int findFrequency(const std::string &s, const std::string &pattern);

		//! @brief return true if parsing has been successful result ill be in i
		static bool tryParseInteger(const std::string &s, int &i);

		//! @brief return true if parsing has been successful result ill be in f
		static bool tryParseFloat(const std::string &s, float &f);

		//! @brief return true if parsing has been successful result ill be in l
		static bool tryParseLong(const std::string &s, long &l);

		//! @brief split a string with a delim char
		static std::vector<std::string> splitStr(const std::string &str, char delim);
	};


}