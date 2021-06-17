//
// Created by cbihan on 01/06/2021.
//

#include "AnimationsComponent.hpp"
#include "Entity/Entity.hpp"
#include "Model/ModelAnimations.hpp"

namespace BBM
{
	AnimationsComponent::AnimationsComponent(WAL::Entity &entity, const std::string &path, int animIndex, bool play)
		: WAL::Component(entity),
		  _modelAnimation(path),
		  _currentAnimIndex(animIndex),
		  _animDisabled(!play)
	{
		this->_modelAnimation[this->_currentAnimIndex].setFrameCounter(0);
	}

	WAL::Component *AnimationsComponent::clone(WAL::Entity &entity) const
	{
		return new AnimationsComponent(entity,
		                               this->_modelAnimation.getFilePath(),
		                               this->_currentAnimIndex);
	}

	size_t AnimationsComponent::getCurrentAnimFrameCounter() const
	{
		return this->_modelAnimation.at(this->_currentAnimIndex).getFrameCounter();
	}

	RAY::ModelAnimation AnimationsComponent::getCurrentModelAnim()
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

	void AnimationsComponent::setAnimDisabled(bool disable)
	{
		this->_animDisabled = disable;
	}

	bool AnimationsComponent::isAnimDisabled() const
	{
		return this->_animDisabled;
	}
}