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
            //! @brief A default destructor
            virtual ~Surface() = 0;

            //! @brief draw rectangle
            virtual void draw(const Rectangle &) = 0;

            //! @brief draw Line
            virtual void draw(const Line &) = 0;

            //! @brief draw Point
            virtual void draw(const Point &) = 0;

            //! @brief draw Circle
            virtual void draw(const Circle &) = 0;

        protected:
        private:
    };
}

#endif /* !SURFACE_HPP_ */
