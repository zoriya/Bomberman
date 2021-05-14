/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Surface
*/

#ifndef SURFACE_HPP_
#define SURFACE_HPP_

#include "Drawables/Drawable.hpp"

namespace Ray {
    class Surface {
        public:
            virtual ~Surface() = 0;

            virtual void draw(const Rectangle &) = 0;
            virtual void draw(const Line &) = 0;
            virtual void draw(const Point &) = 0;
            virtual void draw(const Circle &) = 0;

        protected:
        private:
    };
}

#endif /* !SURFACE_HPP_ */
