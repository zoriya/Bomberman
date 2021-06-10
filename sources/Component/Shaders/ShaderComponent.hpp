//
// Created by cbihan on 03/06/2021.
//

#pragma once

#include <string>
#include <Component/Component.hpp>
#include <Entity/Entity.hpp>
#include <Shaders/Shaders.hpp>
#include <Model/Model.hpp>

namespace BBM
{
	class ShaderComponent : public WAL::Component
	{
	private:
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
		RAY::Drawables::Drawables3D::Model *model = nullptr;

		void onStart() override;

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

	class ShaderComponentDrawable2D : public ShaderComponent
	{
	public:
		//! @brief ctor
		//! @note use empty string to omit a file
		ShaderComponentDrawable2D(WAL::Entity &entity, std::string fragmentFilePath, std::string vertexFilePath = "");
		//! @brief Default copy ctor
		ShaderComponentDrawable2D(const ShaderComponentDrawable2D &) = default;
		//! @brief Default dtor
		~ShaderComponentDrawable2D() override = default;
		//! @brief Default assignment operator
		ShaderComponentDrawable2D &operator=(const ShaderComponentDrawable2D &) = delete;
	};
}