/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Grid
*/

#ifndef GRID_HPP_
#define GRID_HPP_

#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
	//! @brief a grid (centered at (0, 0, 0))
	class Grid: public ADrawable3D
	{
		public:
			//! @brief Grid constructor
			//! @param slices slices of the grid
			//! @param spacing spacing of slices
			Grid(int slices, float spacing, const Color &color = LIGHTGRAY);

			//! @brief A default copy constructor
			Grid(const Grid &) = default;

			//! @brief A Grid is assignable
			Grid &operator=(const Grid &) = default;

			//! @brief A default destructor
			~Grid() override = default;

			//! @return the slices of the Grid
			int getSlices(void) const;

			//! @return the spacing of the Grid
			float getSpacing(void) const;

			//! @brief Set slices
			Grid &setSlices(int slices);

			//! @brief Set spacing
			Grid &setSpacing(float spacing);

			//! @throw NotSupportedError
			//! @remark The grid does not have a position
			const Vector3 &getPosition(void) const override;
			
			//! @throw NotSupportedError
			//! @remark The grid does not have a position
			virtual Grid &setPosition(const Vector3 &position) override;

			//! @brief Draw point on window
			void drawOn(RAY::Window &) override;

			//! @brief Get the bounding box
			BoundingBox getBoundingBox(void) const override;
		private:
			//! @brief Grid slices
			int _slices;
			//! @brief Slices spacing
			float _spacing;
	};
};



#endif /* !GRID_HPP_ */
