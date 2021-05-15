/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <raylib.h>
#include "Drawables/ADrawable2D.hpp"

namespace Ray::Drawable3D {
    class Rectangle: public ADrawable2D
	{
        public:
            //! @brief Rectangle constructor
            //! @param position position of top-left point (in percentage) 
            //! @param dimensions dimensions of the rectangle (in percentage)
            //! @param Color Color of the rectangle  
            Rectangle(Vector2 position, Vector2 dimensions, Color);

            //! @brief Rectangle constructor
            //! @param x x-position of top-left point (in percentage) 
            //! @param y y-position of top-left point (in percentage)
            //! @param width width of the rectangle (in percentage)
            //! @param length length of the rectangle (in percentage)
            //! @param Color Color of the rectangle  
            Rectangle(int x, int y, int width, int height, Color);
            
            //! @brief A default copy constructor
            Rectangle(const Rectangle &) = default;

            //! @brief A rectangle is assignable
            Rectangle &operator=(const Rectangle &) = default;

            //! @brief A default destructor
            ~Rectangle() = default;

            //! @return the dimensions of the rectangle
            const Vector2 &getDimensions(void);

            //! @brief set dimensions
            Rectangle &setDimensions(const Vector2 &position);

            //! @brief set dimensions
            Rectangle &setDimensions(int x, int y);

        private:
            //! @brief Diemnsions of the rectangle (in percentage)
            Vector2 _dimensions;
    };
};

#endif /* !PIXEL_HPP_ */
