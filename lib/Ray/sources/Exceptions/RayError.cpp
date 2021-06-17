/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** RayError
*/

#include "RayError.hpp"

RAY::Exception::RayError::RayError(const std::string &expectionMessage):
	runtime_error(expectionMessage)
{
}

RAY::Exception::NotSupportedError::NotSupportedError(const std::string &expectionMessage):
	RayError(expectionMessage)
{
}

RAY::Exception::NotCompatibleError::NotCompatibleError(const std::string &expectionMessage):
	RayError(expectionMessage)
{
}

RAY::Exception::WrongInputError::WrongInputError(const std::string &what):
	RayError(what)
{
}

RAY::Exception::ResourceNotFound::ResourceNotFound(const std::string &path):
	RayError(path + " couldn't be loaded")
{
}
