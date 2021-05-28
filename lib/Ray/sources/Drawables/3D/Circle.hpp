/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef CIRCLE3D_HPP_
#define CIRCLE3D_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"
#include "BoundingBox.hpp"

namespace RAY::Drawables::Drawables3D {
	//! @brief Circle in a three-dimensionnal space
	class Circle: public ADrawable3D
	{
		public:
			//! @brief Circle constructor
			//! @param centerPosition position of the center 
			//! @param radius radius of the circle
			//! @param Color Color of the circle  
			Circle(const Vector3 &centerPosition, int radius, const Color &color, const Vector3 &rotationAxis, float rotationAngle = 0);

			
			//! @brief A default copy constructor
			Circle(const Circle &) = default;

			//! @brief A circle is assignable
			Circle &operator=(const Circle &) = default;

			//! @brief A default destructor
			~Circle() override = default;

			//! @return the radius of the circle
			int getRadius(void) const;

			//! @brief set radius
			Circle &setRadius(int radius);

			//! @return the position of the center
			const Vector3 &getCenterPos(void) const;

			//! @brief Draw circle on window
			void drawOn(RAY::Window &) override;

			//! @brief Get the bounding box
			BoundingBox getBoundingBox(void) const override;

		private:
			//! @brief Radius of the circle 
			int _radius;

			//! @brief rotation axis
			Vector3 _rotationAxis;
			
			//! @brief rotation angle
			float _rotationAngle;
	};
};

#endif /* !PIXEL_HPP_ */
