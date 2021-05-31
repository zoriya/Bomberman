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
	std::unordered_map<std::string, std::shared_ptr<::Image>> Image::_modelsCache;

	Image::Image(const std::string &filename):
		ADrawable2D(Vector2(0, 0), WHITE),
		_image(fetchImageInCache(filename))
	{
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
	Image &Image::resize(const Vector2 &dimensions)
	{
		ImageResize(this->_image.get(), dimensions.x, dimensions.y);
		return *this;
	}
    
    Vector2 Image::getDimensions() const
	{
		return Vector2(this->_image->width, this->_image->height);
	}
	std::shared_ptr<::Image> Image::fetchImageInCache(const std::string &path)
	{
		if (Image::_modelsCache.find(path) == Image::_modelsCache.end())
			Image::_modelsCache.emplace(path, std::shared_ptr<::Image>(
			new ::Image(LoadImage(path.c_str())), [](::Image *p) {
	       		UnloadImage(*p);
	       		delete p;
	    	}));
		return _modelsCache[path];
	}

	void Image::draw(Drawables::ADrawable2D &drawable)
	{
		drawable.drawOn(*this);
	}

	void Image::drawOn(RAY::Window &)
	{
		Texture texture(*this);

		DrawTexture(texture, this->_position.x, this->_position.y, this->_color); 
	}

	void Image::drawOn(RAY::Image &image)
	{
		Drawables::Drawables2D::Rectangle dest(this->_position, this->getDimensions());
		Drawables::Drawables2D::Rectangle src(Vector2(0, 0), this->getDimensions());
		
		ImageDraw(image, *this, dest, src, this->_color);
	}
}