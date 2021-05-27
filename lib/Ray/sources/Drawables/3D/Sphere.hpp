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
	//! @brief Sphere in a three-dimensionnal space
	class Sphere: public ADrawable3D
	{
		public:
			//! @brief Sphere constructor
			//! @param centerPosition position of the center 
			//! @param radius radius of the sphere
			//! @param Color Color of the sphere  
			Sphere(const Vector3 &centerPosition, int radius, const Color &color);
			
			//! @brief A default copy constructor
			Sphere(const Sphere &) = default;

			//! @brief A sphere is assignable
			Sphere &operator=(const Sphere &) = default;

			//! @brief A default destructor
			~Sphere() override = default;

			//! @return the radius of the sphere
			int getRadius(void) const;

			//! @brief set radius
			Sphere &setRadius(int radius);

			//! @brief Draw point on window
			void drawOn(RAY::Window &) override;

			//! @brief Get the bounding box
			BoundingBox getBoundingBox(void) override;
		private:
			//! @brief Radius of the sphere 
			int _radius;
	};
};

#endif /* !PIXEL_HPP_ */
