/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Image
*/

#include "Drawables/Image.hpp"
#include "Drawables/IDrawable.hpp"
#include "Drawables/Texture.hpp"

RAY::Image::Image(const std::string &filename):
	_image(LoadImage(filename.c_str()))
{
}

RAY::Image::Image(RAY::Texture &texture):
	_image(GetTextureData(texture))
{

}

RAY::Image::~Image()
{
	UnloadImage(_image);
}

bool RAY::Image::exportTo(const std::string &outputPath)
{
	ExportImage(_image, outputPath.c_str());
	return true;
}

RAY::Image::operator ::Image() const
{
	return _image;
}

RAY::Image::operator ::Image *()
{
	return &this->_image;
}

RAY::Image &RAY::Image::resize(const RAY::Vector2 &dimensions)
{
	ImageResize(*this, dimensions.x, dimensions.y);
	return *this;
}