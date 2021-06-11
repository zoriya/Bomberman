//
// Created by hbenjamin on 11/06/2021.
//

#pramga once

#include <exception>
#include <stdexcept>
#include <string>

namespace BBM {
	class Error : public std::runtime_error
	{
	public:
		//! @brief Create a new exception
		explicit Error(const std::string &what);
		//! @brief An exception is copy constructable
		Error(const Error &) = default;
		//! @brief A default destructor
		~Error() override = default;
		//! @brief A default assignment operator
		Error &operator=(const Error &) = default;
	};

	class ParserError : public Error
	{
	public:
		//! @brief Create a new parser exception
		explicit ParserError(const std::string &what);
		//! @brief A parser exception is copy constructable
		ParserError(const ParserError &) = default;
		//! @brief A default destructor
		~ParserError() override = default;
		//! @brief A default assignment operator
		ParserError &operator=(const ParserError &) = default;
	};
}
