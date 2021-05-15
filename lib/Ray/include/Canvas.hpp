/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Canvas
*/

#ifndef Canvas_HPP_
#define Canvas_HPP_

#include "Drawables/ADrawable2D.hpp"

namespace Ray {
    class Canvas {
        public:
            //! @brief A default destructor
            virtual ~Canvas() = 0;

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

#endif /* !Canvas_HPP_ */
