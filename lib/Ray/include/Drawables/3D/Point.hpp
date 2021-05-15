/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace Ray::Drawable3D {
    class Point: public ADrawable3D
	{
        public:
            //! @brief Point constructor
            //! @param position position of point 
            //! @param Color Color of the circle
            Point(Vector3 position, Color);

            //! @brief A default copy constructor
            Point(const Point &) = default;

            //! @brief A point is assignable
            Point &operator=(const Point &) = default;

            //! @brief A default destructor
            ~Point() = default;

            //! @return the position of the point
            const Vector3 &getPosition(void) const;

            //! @brief Set position
            Point &setPosition(Vector3 Position);
        private:
            //! @brief point position
            Vector3 _position;
    };
};

#endif /* !PIXEL_HPP_ */
