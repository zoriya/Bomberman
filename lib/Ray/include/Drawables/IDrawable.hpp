/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** IDrawable
*/

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

#include "Window.hpp"

namespace RAY::Drawables
{
    class IDrawable {
        public:
            virtual ~IDrawable() = 0;

            virtual void drawOn(Window &) = 0;

        protected:
        private:
    };
}


#endif /* !IDRAWABLE_HPP_ */
