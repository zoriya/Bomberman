/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef LINE_HPP_
#define LINE_HPP_

#include <raylib.h>
#include "Drawables/ADrawable2D.hpp"

namespace RAY::Drawables::Drawables2D {
    class Line: public ADrawable2D
	{
        public:

            //! @brief Line constructor
            //! @param position position of top-left point  
            //! @param length length of the line
            //! @param Color Color of the circle  
            Line(const Vector2 &position, int length, Color);

            //! @brief Line constructor
            //! @param x x-position of top-left point  
            //! @param y y-position of top-left point 
            //! @param length length of the line
            //! @param Color Color of the circle  
            Line(int x, int y, int length, Color);

            //! @brief A default copy constructor
            Line(const Line &) = default;

            //! @brief A line is assignable
            Line &operator=(const Line &) = default;

            //! @brief A default destructor
            ~Line() = default;

            //! @return the length of the line
            int getLength(void) const;

            //! @return the rotation of the line
            int getRotation(void) const;

            //! @brief set length
            Line &setLength(int);

            //! @brief set rotation
            Line &setRotation(int);

            //! @brief Draw line on window
            void drawOn(Window &);
        private:
            //! @brief Length of the line 
            int _length;
            //! @brief Rotation of the line (from origin, in degree)
            int _rotation;
    };
};

#endif /* !PIXEL_HPP_ */
