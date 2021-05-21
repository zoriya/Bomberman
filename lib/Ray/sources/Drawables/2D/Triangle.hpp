/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include <raylib.h>
#include "Drawables/ADrawable2D.hpp"

namespace RAY::Drawables::Drawables2D {
    class Triangle: public ADrawable2D
	{
        public:

            //! @brief Triangle constructor
            //! @param positionA position of A point  
            //! @param positionB position of B point 
            //! @param positionC position of C point  
            //! @param Color Color of the circle  
            Triangle(const Vector2 &positionA, const Vector2 &positionB, const Vector2 &positionC, const Color &color);


            //! @brief A default copy constructor
            Triangle(const Triangle &) = default;

            //! @brief A Triangle is assignable
            Triangle &operator=(const Triangle &) = default;

            //! @brief A default destructor
            ~Triangle() = default;

            //! @return the position of A of the Triangle
            const Vector2 &getPositionA(void) const;

            //! @return the position of B of the Triangle
            const Vector2 &getPositionB(void) const;

            //! @return the position of C of the Triangle
            const Vector2 &getPositionC(void) const;

            //! @brief the position of A of the Triangle
            Triangle &setPositionA(const Vector2 &);

            //! @brief the position of B of the Triangle
            Triangle &setPositionB(const Vector2 &);

            //! @brief the position of C of the Triangle
            Triangle &setPositionC(const Vector2 &);

            //! @brief Draw point on window
            void drawOn(RAY::Window &window);
            //! @brief Draw point on image
            void drawOn(RAY::Image &image);

        private:
            //! @brief Position of B
            Vector2 _posB;
            //! @brief Position of C
            Vector2 _posC;
    };
};

#endif /* !PIXEL_HPP_ */
