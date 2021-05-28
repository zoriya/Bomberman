/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Model
*/

#include "Model/Model.hpp"
#include "Exceptions/RayError.hpp"

namespace RAY::Drawables::Drawables3D {

	Model::Model(const std::string &filename,
	                                          std::optional<std::pair<MaterialType, std::string>> texture,
											  const RAY::Vector3 &position,
											  const RAY::Vector3 &rotationAxis,
											  float rotationAngle,
											  const RAY::Vector3 &scale)
		: ADrawable3D(position, WHITE),
		_model(LoadModel(filename.c_str())),
		_rotationAxis(rotationAxis),
		_rotationAngle(rotationAngle),
		_scale(scale)
	{
		if (texture.has_value())
			this->setTextureToMaterial(texture->first, texture->second);
	}

	Model::Model(const Mesh &mesh)
	: ADrawable3D({0, 0, 0}, WHITE), _model(LoadModelFromMesh(mesh))
	{
	}

	Model::~Model()
	{
		UnloadModel(this->_model);
	}

	bool Model::unloadKeepMeshes()
	{
		UnloadModelKeepMeshes(_model);
		return true;
	}

	bool Model::setAnimation(const RAY::ModelAnimation &animation)
	{
		if (!IsModelAnimationValid(this->_model, animation))
			throw RAY::Exception::NotCompatibleError("The animation is not compatible with the model");
		UpdateModelAnimation(this->_model, animation, animation.getFrameCounter());
		return true;
	}

	bool Model::setTextureToMaterial(Model::MaterialType materialType, const std::string &texturePath)
	{
		this->_textureList.emplace(materialType, texturePath);
		SetMaterialTexture(&this->_model.materials[materialType],
						   materialType,
						   this->_textureList.at(materialType));
		return true;
	}

	Model::operator ::Model() const
	{
		return this->_model;
	}

	int Model::getBoneCount() const
	{
		return this->_model.boneCount;
	}

	Model &Model::setRotationAngle(float rotationAngle)
	{
		this->_rotationAngle = rotationAngle;
		return *this;
	}

	float Model::getRotationAngle(void)
	{
		return this->_rotationAngle;
	}

	Model &Model::setRotationAxis(const RAY::Vector3 &scale)
	{
		this->_scale = scale;
		return *this;
	}

	const RAY::Vector3 &Model::getRotationAxis(void)
	{
		return this->_rotationAxis;
	}

	Model &Model::setScale(const RAY::Vector3 &scale)
	{
		this->_scale = scale;
		return *this;
	}

	const RAY::Vector3 &Model::getScale(void)
	{
		return this->_scale;
	}

	void Model::drawOn(RAY::Window &)
	{
		DrawModelEx(this->_model, this->_position, this->_rotationAxis, this->_rotationAngle, this->_scale, this->_color);
	}
}