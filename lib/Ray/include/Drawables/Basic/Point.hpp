/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include <raylib.h>
#include "Drawables/Drawable.hpp"

namespace Ray {
    class Point: public Drawable
	{
        public:
            Point(Vector2 position, Color);
            Point(int x, int y, Color);
            Point(const Point &);

            Point &operator=(const Point &);

            ~Point() = default;

            bool collide(const Rectangle &);
            bool collide(const Line &);
            bool collide(const Point &);
            bool collide(const Circle &);
    };
};

#endif /* !PIXEL_HPP_ */
