//
// Created by Louis Auzuret on 05/27/21
//

#include "BoundingBox.hpp"

RAY::BoundingBox::BoundingBox(const RAY::Mesh &mesh):
    _boundingBox(GetMeshBoundingBox(mesh))
{

}

RAY::BoundingBox::BoundingBox(const RAY::Vector3 &min, const RAY::Vector3 &max):
    _boundingBox({min, max})
{

}

RAY::BoundingBox::BoundingBox(const ::BoundingBox &boundingBox):
    _boundingBox(boundingBox)
{

}

RAY::BoundingBox::operator ::BoundingBox() const
{
    return this->_boundingBox;
}

bool RAY::BoundingBox::collide(const RAY::BoundingBox &other) const
{
    return CheckCollisionBoxes(*this, other);
}

bool RAY::BoundingBox::collision(const RAY::BoundingBox &one, const RAY::BoundingBox &other)
{
    return one.collide(other);
}

RAY::Vector3 RAY::BoundingBox::getMin() const
{
    return this->_boundingBox.min;
}

RAY::Vector3 RAY::BoundingBox::getMax() const
{
    return this->_boundingBox.max;
}

void RAY::BoundingBox::setMin(const RAY::Vector3 &min)
{
    this->_boundingBox.min = min;
}

void RAY::BoundingBox::setMax(const RAY::Vector3 &max)
{
    this->_boundingBox.max = max;
}