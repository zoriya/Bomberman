/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Texture
*/

#include "Drawables/Texture.hpp"

namespace RAY {

	Texture::Texture(const std::string &filename):
		_texture(LoadTexture(filename.c_str())),
		_resourcePath(filename)
	{
	}

	Texture::Texture(const Texture &texture):
		_texture(LoadTexture(texture._resourcePath.c_str())),
		_resourcePath(texture._resourcePath)
	{
	}


	Texture &Texture::operator=(const Texture &other)
	{
		UnloadTexture(this->_texture);
		this->_resourcePath = other._resourcePath;
		this->_texture = LoadTexture(this->_resourcePath.c_str());
		return *this;
	}

	Texture::~Texture()
	{
		UnloadTexture(this->_texture);
	}

	Texture::operator ::Texture() const
	{
		return this->_texture;
	}
}
