/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Font
*/

#include "Font.hpp"

RAY::Font::Font(const std::string &filename)
{
    this->load(filename);
}

RAY::Font::Font()
{
}

RAY::Font::~Font()
{
    this->unload();
}

bool RAY::Font::load(const std::string &filename)
{
    _font = LoadFont(filename.c_str());
    return true;
}

bool RAY::Font::unload()
{
    UnloadFont(_font);
}
