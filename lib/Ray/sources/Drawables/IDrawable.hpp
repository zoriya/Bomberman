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
                virtual ~IDrawable() = default;

                virtual void drawOn(RAY::Window &window) = 0;
            protected:
            private:
        };
    }
}


#endif /* !IDRAWABLE_HPP_ */
