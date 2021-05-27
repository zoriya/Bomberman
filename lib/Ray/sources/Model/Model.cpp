/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Model
*/

#include "Model/Model.hpp"
#include "Exceptions/RayError.hpp"

RAY::Drawables::Drawables3D::Model::Model(const std::string &filename, const RAY::Vector3 &position, const RAY::Vector3 &rotationAxis, float rotationAngle, const RAY::Vector3 &scale):
	ADrawable3D(position, WHITE), _model(LoadModel(filename.c_str())),
	_rotationAxis(rotationAxis), _rotationAngle(rotationAngle), _scale(scale)
{
}

RAY::Drawables::Drawables3D::Model::Model(const Mesh &mesh)
: ADrawable3D({0, 0, 0}, WHITE), _model(LoadModelFromMesh(mesh))
{
}

RAY::Drawables::Drawables3D::Model::~Model()
{
	this->unload();
}

bool RAY::Drawables::Drawables3D::Model::load(const std::string &filename)
{
	this->_model = LoadModel(filename.c_str());
	return true;
}

bool RAY::Drawables::Drawables3D::Model::load(const Mesh &mesh)
{
	this->_model = LoadModelFromMesh(mesh);
	return true;
}

bool RAY::Drawables::Drawables3D::Model::unload()
{
	UnloadModel(this->_model);
	return true;
}

bool RAY::Drawables::Drawables3D::Model::unloadKeepMeshes()
{
	UnloadModelKeepMeshes(_model);
	return true;
}

bool RAY::Drawables::Drawables3D::Model::setAnimation(const RAY::ModelAnimation &animation)
{
	if (!IsModelAnimationValid(this->_model, animation))
		throw RAY::Exception::NotCompatibleError("The animation is not compatible with the model");
	UpdateModelAnimation(this->_model, animation, animation.getFrameCounter());
	return true;
}

bool RAY::Drawables::Drawables3D::Model::setTextureToMaterial(RAY::Drawables::Drawables3D::Model::MaterialType materialType, const RAY::Texture &texture)
{
	SetMaterialTexture(&this->_model.materials[materialType], materialType, texture);
	return true;
}

RAY::Drawables::Drawables3D::Model::operator ::Model() const
{
	return this->_model;
}

int RAY::Drawables::Drawables3D::Model::getBoneCount() const
{
	return this->_model.boneCount;
}

RAY::Drawables::Drawables3D::Model &RAY::Drawables::Drawables3D::Model::setRotationAngle(float rotationAngle)
{
	this->_rotationAngle = rotationAngle;
	return *this;
}

float RAY::Drawables::Drawables3D::Model::getRotationAngle(void)
{
	return this->_rotationAngle;
}

RAY::Drawables::Drawables3D::Model &RAY::Drawables::Drawables3D::Model::setRotationAxis(const RAY::Vector3 &scale)
{
	this->_scale = scale;
	return *this;
}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Model::getRotationAxis(void)
{
	return this->_rotationAxis;
}

RAY::Drawables::Drawables3D::Model &RAY::Drawables::Drawables3D::Model::setScale(const RAY::Vector3 &scale)
{
	this->_scale = scale;
	return *this;
}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Model::getScale(void)
{
	return this->_scale;
}

void RAY::Drawables::Drawables3D::Model::drawOn(RAY::Window &)
{
	DrawModelEx(this->_model, this->_position, this->_rotationAxis, this->_rotationAngle, this->_scale, this->_color);
}

RAY::BoundingBox RAY::Drawables::Drawables3D::Model::getBoundingBox(void)
{
	RAY::Mesh mesh = _model.meshes[0];
	return GetMeshBoundingBox(mesh);
}