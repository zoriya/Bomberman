/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Model
*/

#include "Model/Model.hpp"
#include "Exceptions/RayError.hpp"
#include <unordered_map>


namespace RAY::Drawables::Drawables3D
{

	RAY::Cache<::Model> Model::_modelsCache(LoadModel, UnloadModel);

	Model::Model(const std::string &filename,
	             bool lonely,
	             std::optional<std::pair<MaterialType, std::string>> texture,
	             const RAY::Vector3 &scale,
	             const RAY::Vector3 &position,
	             const RAY::Vector3 &rotationAxis,
	             float rotationAngle)
		: ADrawable3D(position, WHITE),
		  _model(_modelsCache.fetch(filename, lonely)),
		  _rotationAxis(rotationAxis),
		  _rotationAngle(rotationAngle),
		  _scale(scale)
	{
		if (texture.has_value())
			this->setTextureToMaterial(texture->first, texture->second);
	}

	Model::Model(const Mesh &mesh,
	             std::optional<std::pair<MaterialType, std::string>> texture,
	             const RAY::Vector3 &scale,
	             const RAY::Vector3 &position,
	             const RAY::Vector3 &rotationAxis,
	             float rotationAngle)
		: ADrawable3D(position, WHITE),
		  _model(std::make_shared<::Model>(LoadModelFromMesh(mesh))),
		  _rotationAxis(rotationAxis),
		  _rotationAngle(rotationAngle),
		  _scale(scale)
	{
		if (texture.has_value())
			this->setTextureToMaterial(texture->first, texture->second);
	}

	bool Model::unloadKeepMeshes()
	{
		UnloadModelKeepMeshes(*this->_model);
		return true;
	}

	bool Model::setAnimation(const RAY::ModelAnimation &animation)
	{
		if (!IsModelAnimationValid(*this->_model, animation))
			throw RAY::Exception::NotCompatibleError("The animation is not compatible with the model");
		UpdateModelAnimation(*this->_model, animation, animation.getFrameCounter());
		return true;
	}

	bool Model::setTextureToMaterial(Model::MaterialType materialType, const std::string &texturePath)
	{
		this->_textureList.emplace(materialType, texturePath);
		SetMaterialTexture(&this->_model->materials[materialType],
		                   materialType,
		                   this->_textureList.at(materialType));
		return true;
	}

	Texture &Model::getTextureByMaterial(MaterialType materialType)
	{
		return this->_textureList[materialType];
	}

	Model::operator ::Model() const
	{
		return *this->_model;
	}

	int Model::getBoneCount() const
	{
		return this->_model->boneCount;
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

	Model &Model::setRotationAxis(const RAY::Vector3 &rotationAxis)
	{
		this->_rotationAxis = rotationAxis;
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
		DrawModelEx(*this->_model,
		            this->_position,
		            this->_rotationAxis,
		            this->_rotationAngle,
		            this->_scale,
		            this->_color);
	}

	void Model::drawWiresOn(RAY::Window &)
	{
		if (this->_model->meshCount) {
			::BoundingBox box = GetMeshBoundingBox(*this->_model->meshes);
			box.min.x += this->_position.x;
			box.min.y += this->_position.y;
			box.min.z += this->_position.z;
			box.max.x += this->_position.x;
			box.max.y += this->_position.y;
			box.max.z += this->_position.z;
			DrawBoundingBox(box, this->_debugColor);
		}
	}

	void Model::setShader(const RAY::Shader &shader)
	{
		this->_originalShader = this->_model->materials[0].shader;
		this->_model->materials[0].shader = *shader.getShaderPtr();
	}

	void Model::resetShader()
	{
		this->_model->materials[0].shader = this->_originalShader;
	}
}