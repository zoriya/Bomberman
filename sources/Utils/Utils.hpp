//
// Created by cbihan on 17/06/2021.
//

#pragma once

namespace BBM
{
	struct Utils
	{
		//! @brief trim left end
		static inline void lTrim(std::string &s);

		//! @brief trim right end
		static inline void rTrim(std::string &s);

		//! @brief trim from both ends
		static inline void trim(std::string &s);

		//! @brief trim left end (copying)
		static inline std::string lTrimCopy(std::string s);

		//! @brief trim right end (copying)
		static inline std::string rTrimCopy(std::string s);

		//! @brief trim from both ends (copying)
		static inline std::string trimCopy(std::string s);
	};


}