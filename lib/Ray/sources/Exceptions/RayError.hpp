/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** RayError
*/

#ifndef RAYERROR_HPP_
#define RAYERROR_HPP_

#include <stdexcept>
#include <string>

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


	//! @brief exception used when an non-supported operation is done
	class WrongInputError: public RayError {
	public:
		//! @brief Create a new exception instance
		explicit WrongInputError(const std::string &what = "The input can't be proceed");

		//! @brief A default destructor
		~WrongInputError() override = default;

		//! @brief An exception is copy constructable
		WrongInputError(const WrongInputError &) = default;

		//! @brief A default assignment operator
		WrongInputError &operator=(const WrongInputError &) = default;
	};

		//! @brief exception used when a resource is not found
	class ResourceNotFound: public RayError {
	public:
		//! @brief Create a new exception instance
		//! @param path path of the un-loadable path
		explicit ResourceNotFound(const std::string &path);

		//! @brief A default destructor
		~ResourceNotFound() override = default;

		//! @brief An exception is copy constructable
		ResourceNotFound(const ResourceNotFound &) = default;

		//! @brief A default assignment operator
		ResourceNotFound &operator=(const ResourceNotFound &) = default;
	};
}

#endif /* !RAYERROR_HPP_ */
