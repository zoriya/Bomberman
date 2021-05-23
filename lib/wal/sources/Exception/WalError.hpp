//
// Created by Zoe Roux on 2021-05-14.
//


#pragma once

#include <exception>
#include <stdexcept>

namespace WAL
{
	//! @brief The base class for WAL's exceptions.
	class WalError : public std::runtime_error
	{
	public:
		//! @brief Create a new wal exception
		explicit WalError(const std::string &what);
		//! @brief A wal exception is copy constructable
		WalError(const WalError &) = default;
		//! @brief A default destructor
		~WalError() override = default;
		//! @brief A default assignment operator
		WalError &operator=(const WalError &) = default;
	};

	//! @brief An exception informing the user that something already exists.
	class DuplicateError : public WalError
	{
	public:
		//! @brief Create a new wal exception
		explicit DuplicateError(const std::string &what);
		//! @brief A wal exception is copy constructable
		DuplicateError(const DuplicateError &) = default;
		//! @brief A default destructor
		~DuplicateError() override = default;
		//! @brief A default assignment operator
		DuplicateError &operator=(const DuplicateError &) = default;
	};

	//! @brief An exception informing the user that something could not be found
	class NotFoundError : public WalError
	{
	public:
		//! @brief Create a new wal exception
		explicit NotFoundError(const std::string &what);
		//! @brief A wal exception is copy constructable
		NotFoundError(const NotFoundError &) = default;
		//! @brief A default destructor
		~NotFoundError() override = default;
		//! @brief A default assignment operator
		NotFoundError &operator=(const NotFoundError &) = default;
	};
} // namespace WAL