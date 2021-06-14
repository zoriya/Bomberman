//
// Created by Zoe Roux on 5/24/21.
//

#include "IntroAnimationComponent.hpp"

namespace BBM
{
	IntroAnimationComponent::IntroAnimationComponent(WAL::Entity &entity)
		: WAL::Component(entity)
	{}

	WAL::Component *IntroAnimationComponent::clone(WAL::Entity &entity) const
	{
		return new IntroAnimationComponent(entity);
	}
}