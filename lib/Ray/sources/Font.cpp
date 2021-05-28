/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Font
*/

#include "Font.hpp"

RAY::Font::Font(const std::string &filename):
	_font(LoadFont(filename.c_str()))
{
}

RAY::Font::Font()
{
}

RAY::Font::~Font()
{
	UnloadFont(this->_font);
}
