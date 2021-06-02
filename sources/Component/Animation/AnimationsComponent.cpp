//
// Created by cbihan on 01/06/2021.
//

#include "AnimationsComponent.hpp"
#include "Entity/Entity.hpp"
#include "Model/ModelAnimations.hpp"

namespace BBM
{
	AnimationsComponent::AnimationsComponent(WAL::Entity &entity, RAY::ModelAnimations &modelAnimation, int animIndex)
		: WAL::Component(entity),
		  _modelAnimation(modelAnimation),
		  _currentAnimIndex(animIndex)
	{
		this->_modelAnimation[this->_currentAnimIndex].setFrameCounter(0);
	}

	WAL::Component *AnimationsComponent::clone(WAL::Entity &entity) const
	{
		return new AnimationsComponent(entity, this->_modelAnimation, this->_currentAnimIndex);
	}

	size_t AnimationsComponent::getCurrentAnimFrameCounter() const
	{
		return this->_modelAnimation[this->_currentAnimIndex].getFrameCounter();
	}

	RAY::ModelAnimation AnimationsComponent::getCurrentModelAnim() const
	{
		return this->_modelAnimation[this->_currentAnimIndex];
	}

	void AnimationsComponent::setCurrentAnimFrameCounter(size_t animFrameCounter)
	{
		this->_modelAnimation[this->_currentAnimIndex].setFrameCounter(animFrameCounter);
	}

	void AnimationsComponent::resetCurrentAnimFrameCounter()
	{
		this->_modelAnimation[this->_currentAnimIndex].setFrameCounter(0);
	}

	size_t AnimationsComponent::getCurrentAnimIndex() const
	{
		return this->_currentAnimIndex;
	}

	void AnimationsComponent::setAnimIndex(int animIndex)
	{
		this->_currentAnimIndex = animIndex % static_cast<int>(this->_modelAnimation.getAnimationsCount());
	}

	void AnimationsComponent::incCurrentAnimFrameCounter()
	{
		this->_modelAnimation[this->_currentAnimIndex].incrementFrameCounter();
	}
}