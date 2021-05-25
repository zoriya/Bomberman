/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include <raylib.h>
#include "Drawables/ADrawable2D.hpp"

namespace RAY::Drawables::Drawables2D {
	//! @brief Point in a two-dimensionnal space
	class Point: public ADrawable2D
	{
		public:
			//! @brief Point constructor
			//! @param position position of point  
			//! @param Color Color of the circle
			Point(const Vector2 &position, const Color &);

			//! @brief Point constructor
			//! @param x x-position of point  
			//! @param y y-position of point 
			//! @param Color Color of the circle  
			Point(int x, int y, const Color &);

			//! @brief A default copy constructor
			Point(const Point &) = default;

			//! @brief A point is assignable
			Point &operator=(const Point &) = default;

			//! @brief A default destructor
			~Point() = default;

			//! @brief Draw point on window
			void drawOn(RAY::Window &) override;
			//! @brief Draw point on image
			void drawOn(RAY::Image &image) override;

	};
};

#endif /* !PIXEL_HPP_ */
