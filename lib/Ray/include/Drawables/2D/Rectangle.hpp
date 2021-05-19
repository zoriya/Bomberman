/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef RECTANGLE2D_HPP_
#define RECTANGLE2D_HPP_

#include <raylib.h>
#include "Drawables/ADrawable2D.hpp"

namespace RAY::Drawables::Drawables2D {
    class Rectangle: public ADrawable2D
	{
        public:
            //! @brief Rectangle constructor
            //! @param position position of top-left point  
            //! @param dimensions dimensions of the rectangle 
            //! @param Color Color of the rectangle  
            Rectangle(const Vector2 &position, Vector2 dimensions, Color);

            //! @brief Rectangle constructor
            //! @param x x-position of top-left point  
            //! @param y y-position of top-left point 
            //! @param width width of the rectangle 
            //! @param length length of the rectangle 
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

            //! @brief Draw rectangle on window
            void drawOn(Window &);

        private:
            //! @brief Diemnsions of the rectangle 
            Vector2 _dimensions;
    };
};

#endif /* !PIXEL_HPP_ */
