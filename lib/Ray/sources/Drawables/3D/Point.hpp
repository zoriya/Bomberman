/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef POINT3D_HPP_
#define POINT3D_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
	//! @brief Point in a three-dimensionnal space
	class Point: public ADrawable3D
	{
		public:
			//! @brief Point constructor
			//! @param position position of point 
			//! @param Color Color of the point
			Point(const Vector3 &position, const Color &color);

			//! @brief A default copy constructor
			Point(const Point &) = default;

			//! @brief A point is assignable
			Point &operator=(const Point &) = default;

			//! @brief A default destructor
			~Point() = default;

			//! @brief Draw point on window
			void drawOn(RAY::Window &) override;
	};
};

#endif /* !PIXEL_HPP_ */
