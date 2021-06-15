//
// Created by cbihan on 04/06/2021.
//

#include "Shaders.hpp"

#include <utility>
#include "Exceptions/RayError.hpp"

namespace RAY
{
	Cache<::Shader> Shader::_shadersCache(LoadShader, UnloadShader);


	Shader::Shader(const std::string &vertexFile, const std::string &fragmentFile)
		: _vertexFile(vertexFile),
		  _fragmentFile(fragmentFile),
		  _rayLibShader(_shadersCache.fetch(vertexFile, fragmentFile))
	{
		this->_rayLibShader->locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(*this->_rayLibShader, "mask");
	}

	const std::shared_ptr<::Shader> &Shader::getShaderPtr() const
	{
		return this->_rayLibShader;
	}

	void Shader::setShaderUniformVar(const std::string &varName, float value)
	{
		if (this->_shaderIndexVars.find(varName) == this->_shaderIndexVars.end()) {
			int varShaderIndex = GetShaderLocation(*this->_rayLibShader, varName.c_str());

			if (varShaderIndex < 0) {
				throw Exception::WrongInputError("The loaded shader doesn't have a variable called: " + varName);
			}
			this->_shaderIndexVars[varName] = varShaderIndex;
		}
		SetShaderValue(*this->_rayLibShader, this->_shaderIndexVars[varName], &value, SHADER_UNIFORM_FLOAT);
	}

	void Shader::setShaderUniformVar(const std::string &varName, int value)
	{
		if (this->_shaderIndexVars.find(varName) == this->_shaderIndexVars.end()) {
			int varShaderIndex = GetShaderLocation(*this->_rayLibShader, varName.c_str());

			if (varShaderIndex < 0) {
				throw Exception::WrongInputError("The loaded shader doesn't have a variable called: " + varName);
			}
			this->_shaderIndexVars[varName] = varShaderIndex;
		}
		SetShaderValue(*this->_rayLibShader, this->_shaderIndexVars[varName], &value, SHADER_UNIFORM_INT);
	}

	void Shader::BeginUsingCustomShader(Shader &shader)
	{
		BeginShaderMode(*shader.getShaderPtr());
	}

	void Shader::EndUsingCustomShader()
	{
		EndShaderMode();
	}
}