//
// Created by hbenjamin on 03/06/2021.
//

#include "AnimatorComponent.hpp"

namespace BBM {
	AnimatorComponent::AnimatorComponent(WAL::Entity &entity)
			: WAL::Component(entity)
	{}

	WAL::Component *AnimatorComponent::clone(WAL::Entity &entity) const
	{
		return new AnimatorComponent(entity);
	}
}