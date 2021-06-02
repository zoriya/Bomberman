/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Texture
*/

#include "Drawables/Texture.hpp"
#include "Exceptions/RayError.hpp"

namespace RAY {

	Texture::Texture(const std::string &filename):
		ADrawable2D(0, 0, WHITE),
		_texture(LoadTexture(filename.c_str())),
		_resourcePath(filename)
	{
	}

	Texture::Texture(const Texture &texture):
		ADrawable2D(0, 0, WHITE),
		_texture(LoadTexture(texture._resourcePath.c_str())),
		_resourcePath(texture._resourcePath)
	{
	}


	Texture &Texture::operator=(const Texture &other)
	{
		this->_resourcePath = other._resourcePath;
		this->_texture = LoadTexture(this->_resourcePath.c_str());
		return *this;
	}

	Texture::~Texture()
	{
		UnloadTexture(this->_texture);
	}

	void Texture::drawOn(RAY::Window &)
	{
		DrawTexture(this->_texture, this->_position.x, this->_position.y, this->_color);
	}

	void Texture::drawOn(RAY::Image &)
	{
		throw RAY::Exception::NotSupportedError("A texture cannot be drawn on an image");
	}

	Texture::operator ::Texture() const
	{
		return this->_texture;
	}

	bool Texture::isCoordInside(Vector2 coord)
	{
		return (coord.x >= _position.x && coord.x <= _position.x + _texture.width &&
				coord.y >= _position.y && coord.y <= _position.y + _texture.height);
	}
}
