/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Mesh
*/

#include "Mesh.hpp"

RAY::Mesh::Mesh(const ::Mesh &mesh):
    _mesh(mesh)
{

}

RAY::Mesh::operator ::Mesh() const
{
    return this->_mesh;
}

bool RAY::Mesh::exportTo(const std::string &file)
{
    return ExportMesh(this->_mesh, file.c_str());
}