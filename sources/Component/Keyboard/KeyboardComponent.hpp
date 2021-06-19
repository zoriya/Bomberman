//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include <Controllers/Keyboard.hpp>
#include "Component/Component.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"

using Key = RAY::Controller::Keyboard::Key;

namespace BBM
{
	class KeyboardComponent : public WAL::Component
	{
	public:
		//! @brief jump key
		Key keySecondary = KEY_SPACE;
		//! @brief bomb key
		Key keyBomb = KEY_E;
		//! @brief pause key
		Key keyPause = KEY_ESCAPE;
		//! @brief move right key
		Key keyRight = KEY_D;
		//! @brief move left key
		Key keyLeft = KEY_A;
		//! @brief move up key
		Key keyUp = KEY_W;
		//! @brief move down key
		Key keyDown = KEY_S;
		//! @brief Layout
		ControllableComponent::Layout layout;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		void onStart() override;

		//! @brief Create a new keyboard component using custom keys.
		explicit KeyboardComponent(WAL::Entity &entity, ControllableComponent::Layout controllerLayout = ControllableComponent::Layout::KEYBOARD_0);

		//! @brief A Keyboard component is copy constructable.
		KeyboardComponent(const KeyboardComponent &) = default;

		//! @brief default destructor
		~KeyboardComponent() override = default;

		//! @brief A Keyboard component can't be assigned
		KeyboardComponent &operator=(const KeyboardComponent &) = delete;
	};
}