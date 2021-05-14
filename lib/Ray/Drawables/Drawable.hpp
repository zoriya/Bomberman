/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <raylib.h>
#include <Vector.hpp>

namespace Ray {
    struct Drawable
	{
        //top-left position
        Vector2 position;

        Color color;

        virtual ~Drawable() = 0;
    };
};

#endif /* !DRAWABLE_HPP_ */
