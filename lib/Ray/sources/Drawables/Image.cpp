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

const ::Image &RAY::Image::getImage(void) const
{
    return _image;
}