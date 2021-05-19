/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** IDrawable
*/

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

namespace RAY
{
    class Canvas;
    namespace Drawables {
        class IDrawable {
            public:
                virtual ~IDrawable() = 0;

                virtual void drawOn(RAY::Canvas &) = 0;

            protected:
            private:
        };
    }
}


#endif /* !IDRAWABLE_HPP_ */
