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