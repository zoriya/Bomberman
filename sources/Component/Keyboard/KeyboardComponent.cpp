//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include <Component/Controllable/ControllableComponent.hpp>
#include "KeyboardComponent.hpp"

namespace BBM
{
	KeyboardComponent::KeyboardComponent(WAL::Entity &entity, ControllableComponent::Layout controllerLayout)
		: WAL::Component(entity), layout(controllerLayout)
	{
		if (layout == ControllableComponent::KEYBOARD_0) {
			this->keyUp = KEY_W;
			this->keyDown = KEY_S;
			this->keyLeft = KEY_A;
			this->keyRight = KEY_D;
			this->keyJump = KEY_SPACE;
			this->keyBomb = KEY_E;
			this->keyPause = KEY_ESCAPE;
		} else {
			this->keyUp = KEY_UP;
			this->keyDown = KEY_DOWN;
			this->keyLeft = KEY_LEFT;
			this->keyRight = KEY_RIGHT;
			this->keyJump = KEY_RIGHT_CONTROL;
			this->keyBomb = KEY_ENTER;
			this->keyPause = KEY_BACKSPACE;
		}
	}

	WAL::Component *KeyboardComponent::clone(WAL::Entity &entity) const
	{
		return new KeyboardComponent(entity, this->layout);
	}

	void KeyboardComponent::onStart()
	{
		auto *controller = this->_entity.tryGetComponent<ControllableComponent>();
		if (!controller)
			return;
		controller->layout = this->layout;
	}

} // namespace BMM
