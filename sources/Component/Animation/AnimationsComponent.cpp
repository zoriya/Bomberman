//
// Created by cbihan on 01/06/2021.
//

#include "AnimationsComponent.hpp"
#include "Entity/Entity.hpp"
#include "Model/ModelAnimations.hpp"

namespace BBM
{
	AnimationsComponent::AnimationsComponent(WAL::Entity &entity, RAY::ModelAnimations &modelAnimation)
		: WAL::Component(entity),
		  _modelAnimation(modelAnimation),
		  _animFrameCounter(0)
	{
	}

	WAL::Component *AnimationsComponent::clone(WAL::Entity &entity) const
	{
		return new AnimationsComponent(entity, this->_modelAnimation);
	}

	size_t AnimationsComponent::getAnimFrameCounter() const
	{
		return this->_animFrameCounter;
	}

	RAY::ModelAnimation AnimationsComponent::getCurrentModelAnim() const
	{
		return this->_modelAnimation[static_cast<int>(this->_animFrameCounter)];
	}

	void AnimationsComponent::setAnimFrameCounter(size_t animFrameCounter)
	{
		this->_animFrameCounter = animFrameCounter;
		this->_animFrameCounter %= this->_modelAnimation.getAnimationsCount();
	}

	void AnimationsComponent::resetAnimFrameCounter()
	{
		this->_animFrameCounter = 0;
	}
}