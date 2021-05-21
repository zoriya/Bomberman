/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Sphere
*/

#include "Drawables/3D/Sphere.hpp"

RAY::Drawables::Drawables3D::Sphere::Sphere(const Vector3 &centerPosition, int radius, const Color &color):
    ADrawable3D(color), _radius(radius), _centerPos(centerPosition)
{

}

int RAY::Drawables::Drawables3D::Sphere::getRadius(void) const
{
    return this->_radius;
}

RAY::Drawables::Drawables3D::Sphere &RAY::Drawables::Drawables3D::Sphere::setRadius(int radius)
{
    this->_radius = radius;
    return *this;
}

const Vector3 &RAY::Drawables::Drawables3D::Sphere::getCenterPos(void) const
{
    return this->_centerPos;
}

RAY::Drawables::Drawables3D::Sphere &RAY::Drawables::Drawables3D::Sphere::setRadius(const Vector3 &pos)
{
    this->_centerPos = pos;
    return *this;
}

void RAY::Drawables::Drawables3D::Sphere::drawOn(RAY::Window &window)
{
    (void)window;
    DrawSphere(this->_centerPos, this->_radius, this->_color.getColor());
}
