/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
    class Sphere: public ADrawable3D
	{
        public:
            //! @brief Sphere constructor
            //! @param centerPosition position of the center 
            //! @param radius radius of the sphere
            //! @param Color Color of the sphere  
            Sphere(const Vector3 &centerPosition, int radius, Color color);

            
            //! @brief A default copy constructor
            Sphere(const Sphere &) = default;

            //! @brief A sphere is assignable
            Sphere &operator=(const Sphere &) = default;

            //! @brief A default destructor
            ~Sphere() = default;

            //! @return the radius of the sphere
            int getRadius(void) const;

            //! @brief set radius
            Sphere &setRadius(int radius) const;

            //! @return the position of the center
            const Vector3 &getCenterPos(void) const;

            //! @brief set pos of center 
            Sphere &setRadius(const Vector3 &pos) const;

            //! @brief Draw point on window
            void drawOn(RAY::Window &window);
            //! @brief Draw point on image
            void drawOn(RAY::Image &image);

        private:
            //! @brief Radius of the sphere 
            int _radius;

            //! @brief position of the center
            Vector3 _centerPos;
    };
};

#endif /* !PIXEL_HPP_ */
