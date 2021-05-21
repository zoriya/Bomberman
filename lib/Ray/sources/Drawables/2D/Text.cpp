/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Text
*/

#include "Drawables/2D/Text.hpp"

RAY::Drawables::Drawables2D::Text::Text(const std::string &content, int fontSize, const Vector2 &position, const Color &color):
	ADrawable2D(position, color), _text(content), _size(fontSize), _spacing(DEFAULT_LETTER_SPACING)
{
	this->_font.recs = nullptr;
}

RAY::Drawables::Drawables2D::Text::Text(const std::string &content, int fontSize, int x, int y, const Color &color):
	ADrawable2D(x, y, color), _text(content), _size(fontSize), _spacing(DEFAULT_LETTER_SPACING)
{
	this->_font.recs = nullptr;
}

const std::string &RAY::Drawables::Drawables2D::Text::getString(void)
{
	return this->_text;
}

int RAY::Drawables::Drawables2D::Text::getFontSize(void)
{
	return this->_size;
}

RAY::Drawables::Drawables2D::Text &RAY::Drawables::Drawables2D::Text::setFont(const Font &font)
{
	this->_font = font;
	return *this; 
}

RAY::Drawables::Drawables2D::Text &RAY::Drawables::Drawables2D::Text::setText(const std::string &text)
{
	this->_text = text;
	return *this; 
}

RAY::Drawables::Drawables2D::Text &RAY::Drawables::Drawables2D::Text::setFontSize(int size)
{
	this->_size = size;
	return *this; 
}

int RAY::Drawables::Drawables2D::Text::getLetterSpacing(void)
{
	return this->_spacing;
}

RAY::Drawables::Drawables2D::Text &RAY::Drawables::Drawables2D::Text::setLetterSpacing(int spacing)
{
	this->_spacing = spacing;
	return *this;
}

void RAY::Drawables::Drawables2D::Text::drawOn(RAY::Window &)
{
	if (!this->_font.recs)
		DrawText(this->_text.c_str(), this->_position.x, this->_position.y,
		this->_size, this->_color.getColor());
	else
		DrawTextEx(this->_font, this->_text.c_str(), this->_position,
		this->_size, this->_spacing, this->_color.getColor());
}

void RAY::Drawables::Drawables2D::Text::drawOn(RAY::Image &image)
{
	if (!this->_font.recs)
		ImageDrawText(&(image.getImage()), this->_text.c_str(), this->_position.x, this->_position.y,
		this->_size, this->_color.getColor());
	else
		ImageDrawTextEx(&(image.getImage()), this->_font, this->_text.c_str(), this->_position,
		this->_size, this->_spacing, this->_color.getColor());
}
