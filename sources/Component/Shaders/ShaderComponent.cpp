//
// Created by cbihan on 03/06/2021.
//

#include "ShaderComponent.hpp"

#include <utility>

namespace BBM
{
	WAL::Component *ShaderComponent::clone(WAL::Entity &entity) const
	{
		return new ShaderComponent(*this);
	}

	RAY::Shader &ShaderComponent::getShader()
	{
		return this->_shader;
	}

	ShaderComponent::ShaderComponent(WAL::Entity &entity, const std::string &fragmentFilePath, const std::string &vertexFilePath)
		: WAL::Component(entity),
		  _refEntity(entity),
		  _shader(vertexFilePath, fragmentFilePath),
		  _fragmentFilePath(fragmentFilePath),
		  _vertexFilePath(vertexFilePath)
	{
	}

	std::string ShaderComponent::getFragmentFilePath() const
	{
		return this->_fragmentFilePath;
	}

	std::string ShaderComponent::getVertexFilePath() const
	{
		return this->_vertexFilePath;
	}

	ShaderComponentModel::ShaderComponentModel(WAL::Entity &entity, std::string fragmentFilePath, std::string vertexFilePath)
		: ShaderComponent(entity, std::move(fragmentFilePath), std::move(vertexFilePath))
	{
	}

	ShaderComponentDrawable::ShaderComponentDrawable(WAL::Entity &entity, std::string fragmentFilePath, std::string vertexFilePath)
		: ShaderComponent(entity, std::move(fragmentFilePath), std::move(vertexFilePath))
	{
	}
}