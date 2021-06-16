//
// Created by cbihan on 16/06/2021.
//

#include "BombExplosionShaderComponent.hpp"

namespace BBM
{

	BombExplosionShaderComponent::BombExplosionShaderComponent(WAL::Entity &entity) :
		Component(entity)
	{
	}

	WAL::Component *BombExplosionShaderComponent::clone(WAL::Entity &entity) const
	{
		return new BombExplosionShaderComponent(this->_entity);
	}
}