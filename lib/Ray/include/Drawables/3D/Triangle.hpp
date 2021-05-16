/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef TRIANGLE3D_HPP_
#define TRIANGLE3D_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace Ray::Drawable3D {
    class Triangle: public ADrawable3D
	{
        public:

            //! @brief Triangle constructor
            //! @param positionA position of A point  
            //! @param positionB position of B point 
            //! @param positionC position of C point  
            //! @param Color Color of the circle  
            Triangle(Vector3 positionA, Vector3 positionB, Vector3 positionC,int length, Color);


            //! @brief A default copy constructor
            Triangle(const Triangle &) = default;

            //! @brief A Triangle is assignable
            Triangle &operator=(const Triangle &) = default;

            //! @brief A default destructor
            ~Triangle() = default;

            //! @return the position of A of the Triangle
            Vector3 getPositionA(void) const;

            //! @return the position of B of the Triangle
            Vector3 getPositionB(void) const;

            //! @return the position of C of the Triangle
            Vector3 getPositionC(void) const;

            //! @brief the position of A of the Triangle
            Triangle &setPositionA(Vector3);

            //! @brief the position of B of the Triangle
            Triangle &setPositionB(Vector3);

            //! @brief the position of C of the Triangle
            Triangle &setPositionC(Vector3);


        private:
            //! @brief Position of A
            Vector3 _posA;
            //! @brief Position of B
            Vector3 _posB;
            //! @brief Position of C
            Vector3 _posC;
    };
};

#endif /* !PIXEL_HPP_ */
