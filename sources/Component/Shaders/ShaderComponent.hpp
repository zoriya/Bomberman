//
// Created by cbihan on 03/06/2021.
//

#pragma once

#include <string>
#include <Component/Component.hpp>
#include <Entity/Entity.hpp>
#include <Shaders/Shaders.hpp>

namespace BBM
{
	class ShaderComponent : public WAL::Component
	{
	private:
		//! @brief efefefefez
		WAL::Entity &_refEntity;

		//! @brief The shader to be applied
		RAY::Shader _shader;
		//! @brief The path to the fragment file
		std::string _fragmentFilePath;
		//! @brief The path to the vertex file
		std::string _vertexFilePath;
	public:
		//! @brief getter for _shader
		RAY::Shader &getShader();

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief get the fragment file path
		std::string getFragmentFilePath() const;


		//! @brief get the fragment file path
		std::string getVertexFilePath() const;

		//! @brief ctor
		//! @note use empty string to omit a file
		ShaderComponent(WAL::Entity &entity, const std::string& fragmentFilePath, const std::string& vertexFilePath = "");
		//! @brief Default copy ctor
		ShaderComponent(const ShaderComponent &) = default;
		//! @brief Default dtor
		~ShaderComponent() override = default;
		//! @brief Default assignment operator
		ShaderComponent &operator=(const ShaderComponent &) = delete;
	};

	class ShaderComponentModel : public ShaderComponent
	{
	public:
		//! @brief ctor
		//! @note use empty string to omit a file
		ShaderComponentModel(WAL::Entity &entity, std::string fragmentFilePath, std::string vertexFilePath = "");
		//! @brief Default copy ctor
		ShaderComponentModel(const ShaderComponentModel &) = default;
		//! @brief Default dtor
		~ShaderComponentModel() override = default;
		//! @brief Default assignment operator
		ShaderComponentModel &operator=(const ShaderComponentModel &) = delete;
	};

	class ShaderComponentDrawable : public ShaderComponent
	{
	public:
		//! @brief ctor
		//! @note use empty string to omit a file
		ShaderComponentDrawable(WAL::Entity &entity, std::string fragmentFilePath, std::string vertexFilePath = "");
		//! @brief Default copy ctor
		ShaderComponentDrawable(const ShaderComponentDrawable &) = default;
		//! @brief Default dtor
		~ShaderComponentDrawable() override = default;
		//! @brief Default assignment operator
		ShaderComponentDrawable &operator=(const ShaderComponentDrawable &) = delete;
	};
}