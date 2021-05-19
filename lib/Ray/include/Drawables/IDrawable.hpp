/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** IDrawable
*/

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

#include "Drawables/Image.hpp"
#include "Window.hpp"

namespace RAY
{
    class Window;
    class Image;
    namespace Drawables {
        class IDrawable {
            public:
                virtual ~IDrawable() = 0;

                virtual void drawOn(RAY::Window &window) = 0;

                virtual void drawOn(RAY::Image &image) = 0;

            protected:
            private:
        };
    }
}


#endif /* !IDRAWABLE_HPP_ */
