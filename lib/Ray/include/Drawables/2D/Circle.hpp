/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef CIRCLE2D_HPP_
#define CIRCLE2D_HPP_

#include <raylib.h>
#include "Drawables/ADrawable2D.hpp"

namespace RAY::Drawables::Drawables2D {
    class Circle: public ADrawable2D
	{
        public:
            //! @brief Circle constructor
            //! @param centerPos position of center point  
            //! @param radius radius of the circle
            //! @param Color Color of the circle  
            Circle(const Vector2 &centerPos, int radius, Color color);
            
            //! @brief Circle constructor
            //! @param centerPosX x-position of center point  
            //! @param centerPosY y-position of center point 
            //! @param radius radius of the circle
            //! @param Color Color of the circle  
            Circle(int centerPosX, int centerPosY, int radius, Color color);
            
            //! @brief A default copy constructor
            Circle(const Circle &) = default;

            //! @brief A circle is assignable
            Circle &operator=(const Circle &) = default;

            //! @brief A default destructor
            ~Circle() = default;

            //! @return the radius of the circle
            int getRadius(void) const;

            //! @brief set radius
            Circle &setRadius(int radius);

            //! @brief Draw point on window
            void drawOn(RAY::Window &window);
            //! @brief Draw point on image
            void drawOn(RAY::Image &image);

        private:
            //! @brief Radius of the circle 
            int _radius;
    };
};

#endif /* !PIXEL_HPP_ */
