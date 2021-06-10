//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "KeyboardComponent.hpp"

namespace BBM
{
	KeyboardComponent::KeyboardComponent(WAL::Entity &entity,
							  Key up,
							  Key down,
							  Key left,
							  Key right,
							  Key jump,
							  Key bomb,
							  Key pause)
		: WAL::Component(entity), keyJump(jump), keyBomb(bomb), keyPause(pause),
								  keyRight(right), keyLeft(left), keyUp(up), keyDown(down)
	{}

	WAL::Component *KeyboardComponent::clone(WAL::Entity &entity) const
	{
		return new KeyboardComponent(entity);
	}

} // namespace BMM
