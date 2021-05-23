//
// Created by Zoe Roux on 2021-05-14.
//

#include <string>
#include "WalError.hpp"

namespace WAL
{
	WalError::WalError(const std::string &what)
		: std::runtime_error(what)
	{}

	DuplicateError::DuplicateError(const std::string &what)
		: WalError(what)
	{}

	NotFoundError::NotFoundError(const std::string &what)
		: WalError(what)
	{}
} // namespace WAL