/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Image
*/

#include "Drawables/Image.hpp"

RAY::Image::Image(const std::string &filename):
	_image(LoadImage(filename.c_str()))
{
}

RAY::Image::Image()
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

bool RAY::Image::load(const std::string &filename)
{
	this->_image = LoadImage(filename.c_str());
	return true;
}

bool RAY::Image::exportTo(const std::string &outputPath)
{
	ExportImage(_image, outputPath.c_str());
	return true;
}

bool RAY::Image::unload()
{
	UnloadImage(_image);
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