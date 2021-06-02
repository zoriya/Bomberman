/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Text
*/

#include "Drawables/2D/Text.hpp"

#include <utility>

namespace RAY::Drawables::Drawables2D
{

	Text::Text(std::string content, int fontSize, const Vector2 &position, const Color &color) :
		ADrawable2D(position, color),
		_text(std::move(content)),
		_font({}),
		_size(fontSize),
		_spacing(Text::DefaultLetterSpacing)
	{
		this->_font.recs = nullptr;
	}

	Text::Text(std::string content, int fontSize, int x, int y, const Color &color) :
		ADrawable2D(x, y, color),
		_text(std::move(content)),
		_font({}),
		_size(fontSize),
		_spacing(Text::DefaultLetterSpacing)
	{
		this->_font.recs = nullptr;
	}

	const std::string &Text::getString(void)
	{
		return this->_text;
	}

	int Text::getFontSize(void) const
	{
		return this->_size;
	}

	Text &Text::setFont(const Font &font)
	{
		this->_font = font;
		return *this;
	}

	Text &Text::setText(const std::string &text)
	{
		this->_text = text;
		return *this;
	}

	Text &Text::setFontSize(int size)
	{
		this->_size = size;
		return *this;
	}

	int Text::getLetterSpacing(void) const
	{
		return this->_spacing;
	}

	Text &Text::setLetterSpacing(int spacing)
	{
		this->_spacing = spacing;
		return *this;
	}

	void Text::drawOn(RAY::Window &)
	{
		if (!this->_font.recs)
			DrawText(this->_text.c_str(), this->_position.x, this->_position.y,
			         this->_size, this->_color);
		else
			DrawTextEx(this->_font, this->_text.c_str(), this->_position,
			           this->_size, this->_spacing, this->_color);
	}

	void Text::drawOn(RAY::Image &image)
	{
		if (!this->_font.recs)
			ImageDrawText(image, this->_text.c_str(), this->_position.x, this->_position.y,
			              this->_size, this->_color);
		else
			ImageDrawTextEx(image, this->_font, this->_text.c_str(), this->_position,
			                this->_size, this->_spacing, this->_color);
	}

	bool Text::isCoordInside(Vector2)
	{
		return (false);
	}
}