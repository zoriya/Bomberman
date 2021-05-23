/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
	//! @brief Plane in a three-dimensionnal space
	class Plane: public ADrawable3D
	{
		public:
			//! @brief Plane constructor
			//! @param position position of plane 
			//! @param dimensions dimensions of plane 
			//! @param Color Color of the plane
			Plane(const Vector3 &position, const Vector2 &dimensions, const Color &color);

			//! @brief A default copy constructor
			Plane(const Plane &) = default;

			//! @brief A plane is assignable
			Plane &operator=(const Plane &) = default;

			//! @brief A default destructor
			~Plane() = default;

			//! @return the position of the plane
			const Vector3 &getPosition(void) const;

			//! @brief Set position
			Plane &setPosition(const Vector3 &Position);

			//! @return the dimensions of the plane
			const Vector2 &getDimensions(void) const;

			//! @brief Set dimensions
			Plane &setDimensions(const Vector2 &dimensions);

			//! @brief Draw point on window
			void drawOn(RAY::Window &) override;

		private:
			//! @brief plane position
			Vector3 _position;

			//! @brief plane dimensions
			Vector2 _dimensions;
	};
};

#endif /* !PIXEL_HPP_ */
