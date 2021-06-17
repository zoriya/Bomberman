/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Image
*/

#include "Drawables/Image.hpp"
#include "Drawables/ADrawable2D.hpp"
#include "Drawables/2D/Rectangle.hpp"
#include "Exceptions/RayError.hpp"

namespace RAY {
	Cache<::Image> Image::_imagesCache([] (const char *str) {
		::Image image = LoadImage(str);

		if (image.data == nullptr)
			throw Exception::ResourceNotFound(std::string(str));
		return image;
	}, UnloadImage);

	Image::Image(const std::string &filename, bool lonely):
		Rectangle(Vector2(0, 0), Vector2(0, 0), WHITE),
		_image(_imagesCache.fetch(filename, lonely)),
		_ressourcePath(filename)
	{
		this->_dimensions = Vector2(this->_image->width, this->_image->height);
	}

	bool Image::exportTo(const std::string &outputPath)
	{
		ExportImage(*this->_image, outputPath.c_str());
		return true;
	}

	Image::operator ::Image() const
	{
		return *this->_image;
	}

	Image &Image::use(const std::string &filename)
	{
		if (this->_ressourcePath == filename)
			return *this;
		this->_image = this->_imagesCache.fetch(filename);
		this->_ressourcePath = filename;
		return *this;
	}

	Image::operator ::Image *()
	{
		return this->_image.get();
	}

	void Image::draw(Drawables::ADrawable2D &drawable)
	{
		drawable.drawOn(*this);
	}

	void Image::resize(const RAY::Vector2 &dimensions)
	{
		ImageResize(*this, dimensions.x, dimensions.y);
		this->setDimensions(dimensions);
	}

	void Image::drawOn(RAY::Window &)
	{
		throw RAY::Exception::NotSupportedError("An image cannot be drawn onto a window");
	}

	void Image::drawOn(RAY::Image &image)
	{
		Drawables::Drawables2D::Rectangle dest(this->_position, this->getDimensions());
		Drawables::Drawables2D::Rectangle src(Vector2(0, 0), this->getDimensions());
		
		ImageDraw(image, *this, dest, src, this->_color);
	}
}