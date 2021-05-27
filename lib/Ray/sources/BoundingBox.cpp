//
// Created by Louis Auzuret on 05/27/21
//

#include "BoundingBox.hpp"

RAY::BoundingBox::BoundingBox(const RAY::Mesh &mesh):
    _boundingBox(GetMeshBoundingBox(mesh))
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