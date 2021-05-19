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
    class Window;
    namespace Drawables {
        class IDrawable {
            public:
                virtual ~IDrawable() = 0;

                virtual void drawOn(RAY::Window &) = 0;

            protected:
            private:
        };
    }
}


#endif /* !IDRAWABLE_HPP_ */
