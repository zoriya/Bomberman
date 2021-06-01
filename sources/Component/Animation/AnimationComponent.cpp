//
// Created by cbihan on 01/06/2021.
//

#include "AnimationComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	AnimationComponent::AnimationComponent(WAL::Entity &entity, RAY::ModelAnimation &modelAnimation)
		: WAL::Component(entity),
		_modelAnimation(modelAnimation)
	{

	}
}