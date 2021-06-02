/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Texture
*/

#include "Drawables/Texture.hpp"

namespace RAY {

	Cache<::Texture> Texture::_texturesCache(LoadTexture, UnloadTexture); 

	Texture::Texture(const std::string &filename):
		_texture(_texturesCache.fetch(filename)),
		_resourcePath(filename)
	{
	}

	Texture::Texture(const Image &image):
		_texture(std::make_shared<::Texture>(LoadTextureFromImage(image))),
		_resourcePath()
	{
	}

	Texture::operator ::Texture() const
	{
		return *this->_texture;
	}
}
