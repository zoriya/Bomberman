/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Texture
*/

#include "Drawables/Texture.hpp"

namespace RAY {

	std::unordered_map<std::string, std::shared_ptr<::Texture>> Texture::_textureCache; 

	Texture::Texture(const std::string &filename):
		_texture(fetchTextureInCache(filename)),
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

	std::shared_ptr<::Texture> Texture::fetchTextureInCache(const std::string &path)
	{
		if (Texture::_textureCache.find(path) == Texture::_textureCache.end())
			Texture::_textureCache.emplace(path, std::shared_ptr<::Texture>(
			new ::Texture(LoadTexture(path.c_str())), [](::Texture *p) {
           		UnloadTexture(*p);
           		delete p;
        	}));
		return _textureCache[path];
	}
}
