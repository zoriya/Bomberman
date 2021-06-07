/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Image
*/

#include "Drawables/Image.hpp"
#include "Drawables/ADrawable2D.hpp"
#include "Drawables/2D/Rectangle.hpp"

namespace RAY {
	Cache<::Image> Image::_imagesCache(LoadImage, UnloadImage);

	Image::Image(const std::string &filename):
		Rectangle(Vector2(0, 0), Vector2(0, 0), WHITE),
		_image(_imagesCache.fetch(filename))
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
		//Since the image is a shared object, when it is resized, it mush be resized after to its previous dimensions
		//Vector2 oldDims = Vector2(this->_image->width, this->_image->height);

		//ImageResize(*this, this->_dimensions.x, this->_dimensions.y);
		Texture texture(*this);

		DrawTexture(texture, this->_position.x, this->_position.y, this->_color); 
		//ImageResize(*this, oldDims.x, oldDims.y);
	}

	void Image::drawOn(RAY::Image &image)
	{
		Drawables::Drawables2D::Rectangle dest(this->_position, this->getDimensions());
		Drawables::Drawables2D::Rectangle src(Vector2(0, 0), this->getDimensions());
		
		ImageDraw(image, *this, dest, src, this->_color);
	}
}