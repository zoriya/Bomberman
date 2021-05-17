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
            //! @param topLeftPos position of top-left point  
            //! @param radius radius of the circle
            //! @param Color Color of the circle  
            Circle(Vector2 topLeftPos, int radius, Color color);
            
            //! @brief Circle constructor
            //! @param topLeftX x-position of top-left point  
            //! @param topLeftY y-position of top-left point 
            //! @param radius radius of the circle
            //! @param Color Color of the circle  
            Circle(int topLeftX, int topLeftY, int radius, Color color);
            
            //! @brief A default copy constructor
            Circle(const Circle &) = default;

            //! @brief A circle is assignable
            Circle &operator=(const Circle &) = default;

            //! @brief A default destructor
            ~Circle() = default;

            //! @return the radius of the circle
            int getRadius(void) const;

            //! @brief set radius
            Circle &setRadius(int radius) const;

            //! @brief Draw Circle on window
            void drawOn(Window &);

        private:
            //! @brief Radius of the circle 
            int _radius;
    };
};

#endif /* !PIXEL_HPP_ */
