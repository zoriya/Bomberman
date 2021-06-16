//
// Created by cbihan on 04/06/2021.
//

#pragma once

#include <string>
#include <memory>
#include <map>
#include <raylib.h>
#include "Utils/Cache.hpp"

namespace RAY
{
	class Shader
	{
	private:
		//! @brief The vertex file of the shader
		std::string _vertexFile;
		//! @brief The fragment file of the shader
		std::string _fragmentFile;

		//! @brief Raylib shader struct
		std::shared_ptr<::Shader> _rayLibShader;

		//! @brief Fetch and cache the index of the shader variable on the first set of the var
		std::map<std::string, int> _shaderIndexVars = {};

		static Cache<::Shader> _shadersCache;
	public:
		//INTERNAL:
		const std::shared_ptr<::Shader> &getShaderPtr() const;

	public:

		//! @brief start using a custom shader when drawing
		static void BeginUsingCustomShader(RAY::Shader &shader);
		//! @brief stop using the custom shader
		static void EndUsingCustomShader();

		//! @brief The set var for float values
		//! @note Throw if the var is not found
		void setShaderUniformVar(const std::string &varName, float value);

		//! @brief The set var for float values
		//! @note Throw if the var is not found
		void setShaderUniformVar(const std::string &varName, int value);

		void setLocation(::ShaderLocationIndex, const std::string &name);

		//! @brief ctor if no vertexfile in needed set it to nullptr
		Shader(const std::string &vertexFile, const std::string &fragmentFile, bool lonely = false);
		//! @brief Default copy ctor
		Shader(const Shader &) = default;
		//! @brief dtor
		~Shader() = default;
		//! @brief Assignment operator
		Shader &operator=(const Shader &) = default;
	};

}