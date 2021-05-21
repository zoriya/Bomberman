/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Grid
*/

#include "Drawables/3D/Grid.hpp"

RAY::Drawables::Drawables3D::Grid::Grid(int slices, float spacing):
    ADrawable3D(LIGHTGRAY), _slices(slices), _spacing(spacing)
{

}

int RAY::Drawables::Drawables3D::Grid::getSlices(void) const
{
    return this->_slices;
}

float RAY::Drawables::Drawables3D::Grid::getSpacing(void) const
{
    return this->_spacing;
}

RAY::Drawables::Drawables3D::Grid &RAY::Drawables::Drawables3D::Grid::setSlices(int slices)
{
    this->_slices = slices;
    return *this;
}

RAY::Drawables::Drawables3D::Grid &RAY::Drawables::Drawables3D::Grid::setSpacing(float spacing)
{
    this->_spacing = spacing;
    return *this;
}

void RAY::Drawables::Drawables3D::Grid::drawOn(RAY::Window &window)
{
    (void)window;
    DrawGrid(this->_slices, this->_spacing);
}
