//
// Created by cbihan on 16/06/2021.
//

#include "WhiteShaderComponent.hpp"

namespace BBM
{
	WhiteShaderComponent::WhiteShaderComponent(WAL::Entity &entity) :
		Component(entity)
	{
	}

	WAL::Component *WhiteShaderComponent::clone(WAL::Entity &entity) const
	{
		return new WhiteShaderComponent(this->_entity);
	}
}