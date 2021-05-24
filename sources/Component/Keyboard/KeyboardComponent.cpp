//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "KeyboardComponent.hpp"

namespace BBM
{
	KeyboardComponent::KeyboardComponent(WAL::Entity &entity)
		: WAL::Component(entity)
	{}

	WAL::Component *KeyboardComponent::clone(WAL::Entity &entity) const
	{
		return new KeyboardComponent(entity);
	}

} // namespace BMM
