//
// Created by cbihan on 18/06/2021.
//

#include "AlphaCtxShaderComponent.hpp"


namespace BBM
{

	AlphaVarShaderComponent::AlphaVarShaderComponent(WAL::Entity &entity) :
		WAL::Component(entity)
	{
	}

	WAL::Component *AlphaVarShaderComponent::clone(WAL::Entity &entity) const
	{
		return new AlphaVarShaderComponent(this->_entity);
	}
}