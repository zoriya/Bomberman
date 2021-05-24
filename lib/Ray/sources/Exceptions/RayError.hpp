/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** RayError
*/

#ifndef RAYERROR_HPP_
#define RAYERROR_HPP_

#include <stdexcept>

namespace RAY::Exception {
	//! @brief base exception class for RAY lib
	class RayError: public std::runtime_error {
		public:
			//! @brief Create a new RAY exception
			RayError(const std::string &what);

			//! @brief A default destructor
			~RayError() = default;

			//! @brief A RAY exception is copy constructable
			RayError(const RayError &) = default;

			//! @brief A default assignment operator
			RayError &operator=(const RayError &) = default;
	};

	//! @brief exception used when an incompatibility occurs
	class NotCompatibleError: public RayError {
		public:
			//! @brief Create a new exception instance
			NotCompatibleError(const std::string &what);

			//! @brief A default destructor
			~NotCompatibleError() = default;

			//! @brief An exception is copy constructable
			NotCompatibleError(const NotCompatibleError &) = default;

			//! @brief A default assignment operator
			NotCompatibleError &operator=(const NotCompatibleError &) = default;
	};

	//! @brief exception used when an non-supported operation is done
	class NotSupportedError: public RayError {
		public:
			//! @brief Create a new exception instance
			NotSupportedError(const std::string &what = "This operation is currently not supported");

			//! @brief A default destructor
			~NotSupportedError() = default;

			//! @brief An exception is copy constructable
			NotSupportedError(const NotSupportedError &) = default;

			//! @brief A default assignment operator
			NotSupportedError &operator=(const NotSupportedError &) = default;
	};
}

#endif /* !RAYERROR_HPP_ */
