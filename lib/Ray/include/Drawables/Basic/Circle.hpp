/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include <raylib.h>
#include "Drawables/Drawable.hpp"

namespace Ray {
    class Circle: public Drawable
	{
        public:
            Circle(Vector2 topLeftPos, int radius, Color);
            Circle(int topLeftX, int topLeftY, int radius, Color);
            Circle(const Circle &);

            Circle &operator=(const Circle &);

            ~Circle() = default;

            int getRadius(void) const;

        private:
            int _radius;
    };
};

#endif /* !PIXEL_HPP_ */
