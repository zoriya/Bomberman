/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef LINE_HPP_
#define LINE_HPP_

#include <raylib.h>
#include "Drawables/Drawable.hpp"

namespace Ray {
    class Line: public Drawable
	{
        public:
            Line(Vector2 position, int length, Color);
            Line(int x, int y, int length, Color);
            Line(const Line &) = default;

            Line &operator=(const Line &) = default;

            ~Line() = default;

            int getLength(void) const;
            int getRotation(void) const;

            Line &setLength(int);
            Line &setRotation(int);
        private:
            int _length;
            int _rotation;
    };
};

#endif /* !PIXEL_HPP_ */
