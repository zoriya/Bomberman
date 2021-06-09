//
// Created by cbihan on 03/06/2021.
//

#include "ShaderComponent.hpp"

#include <utility>
#include <Component/Renderer/Drawable3DComponent.hpp>

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

	void ShaderComponentModel::onStart()
	{
		auto &drawable = this->_entity.getComponent<Drawable3DComponent>();
		this->model = dynamic_cast<RAY::Drawables::Drawables3D::Model *>(drawable.drawable.get());
		if (!this->model)
			throw std::runtime_error("No model available with a shader model component. This is unsupported.");
	}

	ShaderComponentDrawable2D::ShaderComponentDrawable2D(WAL::Entity &entity, std::string fragmentFilePath, std::string vertexFilePath)
		: ShaderComponent(entity, std::move(fragmentFilePath), std::move(vertexFilePath))
	{
	}
}