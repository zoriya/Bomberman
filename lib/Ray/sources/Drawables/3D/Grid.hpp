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
            Grid(int slices, float spacing);

            //! @brief A default copy constructor
            Grid(const Grid &) = default;

            //! @brief A Grid is assignable
            Grid &operator=(const Grid &) = default;

            //! @brief A default destructor
            ~Grid() = default;

            //! @return the slices of the Grid
            int getSlices(void) const;

            //! @return the spacing of the Grid
            float getSpacing(void) const;

            //! @brief Set slices
            Grid &setSlices(int slices);

            //! @brief Set spacing
            Grid &setSpacing(float spacing);

            //! @brief Draw point on window
            void drawOn(RAY::Window &window) override;

        private:
            //! @brief Grid slices
            int _slices;
            //! @brief Slices spacing
            float _spacing;
    };
};



#endif /* !GRID_HPP_ */
