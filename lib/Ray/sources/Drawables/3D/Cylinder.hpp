/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
	//! @brief Cylinder in a three-dimensionnal space
	class Cylinder: public ADrawable3D
	{
		public:
			//! @brief Cylinder constructor
			//! @param position position of the center 
			//! @param radiusTop radius at the top  the cylinder
			//! @param radiusBottom radius at the bottom of the cylinder
			//! @param radiusBottom heighth of the cylinder
			//! @param Color Color of the cylinder
			Cylinder(const Vector3 &position, float radiusTop, float radiusBottom, float height, const Color &color);

			
			//! @brief A default copy constructor
			Cylinder(const Cylinder &) = default;

			//! @brief A cylinder is assignable
			Cylinder &operator=(const Cylinder &) = default;

			//! @brief A default destructor
			~Cylinder() override = default;

			//! @return the radius of the cylinder
			int getTopRadius(void) const;

			//! @brief set radius
			Cylinder &setTopRadius(float radius);

			//! @return the radius of the cylinder
			int getBottomRadius(void) const;

			//! @brief set radius
			Cylinder &setBottomRadius(float radius);

			//! @return the Height
			float getHeight(void) const;

			//! @brief the Height
			Cylinder &setHeight(float height);

			//! @brief Draw point on window
			void drawOn(RAY::Window &) override;

			//! @brief Get the bounding box
			BoundingBox getBoundingBox(void) override;
		private:
			//! @brief Radius of the cylinder 
			float _topRadius;

			//! @brief Radius of the cylinder 
			float _bottomRadius;

			//! @brief height of the cylinder 
			float _height;

	};
};

#endif /* !PIXEL_HPP_ */
