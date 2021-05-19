/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include <raylib.h>
#include "Drawables/ADrawable2D.hpp"

namespace RAY::Drawables::Drawables2D {
    class Point: public ADrawable2D
	{
        public:
            //! @brief Point constructor
            //! @param position position of point  
            //! @param Color Color of the circle
            Point(const Vector2 &position, Color);

            //! @brief Point constructor
            //! @param x x-position of point  
            //! @param y y-position of point 
            //! @param Color Color of the circle  
            Point(int x, int y, Color);

            //! @brief A default copy constructor
            Point(const Point &) = default;

            //! @brief A point is assignable
            Point &operator=(const Point &) = default;

            //! @brief A default destructor
            ~Point() = default;

            //! @brief Draw point on window
            void drawOn(Window &);
    };
};

#endif /* !PIXEL_HPP_ */
