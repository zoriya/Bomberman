/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Model
*/

#include "Model.hpp"

RAY::Model::Model(const std::string &filename)
{
    this->load(filename);
}

RAY::Model::Model(const Mesh &mesh)
{
    this->load(mesh);
}

RAY::Model::~Model()
{
    this->unload();
}

bool RAY::Model::load(const std::string &filename)
{
    this->_model = LoadModel(filename.c_str());
    return true;
}

bool RAY::Model::load(const Mesh &mesh)
{
    this->_model = LoadModelFromMesh(mesh);
    return true;
}

bool RAY::Model::unload()
{
    UnloadModel(_model);
    return true;
}

bool RAY::Model::unloadKeepMeshes()
{
    UnloadModelKeepMeshes(_model);
    return true;
}
