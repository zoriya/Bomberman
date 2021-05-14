/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <raylib.h>
#include "Drawables/Drawable.hpp"

namespace Ray {
    class Rectangle: public Drawable
	{
        public:
            Rectangle(Vector2 position, Vector2 dimensions,int length, Color);
            Rectangle(int x, int y, int width, int height, int length, Color);
            Rectangle(const Rectangle &);

            Rectangle &operator=(const Rectangle &);

            ~Rectangle() = default;

            const Vector2 &getDimensions(void);

            Rectangle &setDimensions(const Vector2 &position);
            Rectangle &setDimensions(int x, int y);

        private:
            Vector2 _dimensions;
    };
};

#endif /* !PIXEL_HPP_ */
