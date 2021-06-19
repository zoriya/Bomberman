//
// Created by hbenjamin on 11/06/2021.
//

#include "Error.hpp"

namespace BBM
{
	Error::Error(const std::string &what)
			: std::runtime_error(what)
	{}

	ParserError::ParserError(const std::string &what)
			: Error(what)
	{}
} // namespace BBM