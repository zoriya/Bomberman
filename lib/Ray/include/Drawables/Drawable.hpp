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
#include "Drawables/Basic/Circle.hpp"
#include "Drawables/Basic/Line.hpp"
#include "Drawables/Basic/Rectangle.hpp"
#include "Drawables/Basic/Point.hpp"

namespace Ray {
    class Drawable
	{
        public:
            Drawable(Vector2 position, Color color);
            Drawable(int x, int y, Color color);
            virtual ~Drawable() = 0;

            const Vector2 &getPosition(void) const;
            const Color &getColor(void) const;

            Drawable &setPosition(const Vector2 &position);
            Drawable &setPosition(int x, int y);
            Drawable &setColor(const Color &color) const;

            virtual bool collide(const Rectangle &) = 0;
            virtual bool collide(const Line &) = 0;
            virtual bool collide(const Point &) = 0;
            virtual bool collide(const Circle &) = 0;

        private:
            //top-left position
            Vector2 _position;
            Color _color;

    };
};

#endif /* !DRAWABLE_HPP_ */
