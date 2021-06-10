//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include <Controllers/Keyboard.hpp>
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

using Key = RAY::Controller::Keyboard::Key;

namespace BBM
{
	class KeyboardComponent : public WAL::Component
	{
		public:
			//! @brief jump key
			Key keyJump = KEY_SPACE;
			//! @brief bomb key
			Key keyBomb = KEY_E;
			//! @brief pause key
			Key keyPause = RAY::Controller::Keyboard::Key::KEY_ESCAPE;
			//! @brief move right key
			Key keyRight = KEY_D;
			//! @brief move left key
			Key keyLeft = KEY_A;
			//! @brief move up key
			Key keyUp = KEY_W;
			//! @brief move down key
			Key keyDown = KEY_S;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;
		
			//! @brief Create a new keyboard component using custom keys.
			KeyboardComponent(WAL::Entity &entity,
							  Key up = KEY_W,
							  Key down = KEY_S,
							  Key left = KEY_A,
							  Key right = KEY_D,
							  Key jump = KEY_SPACE,
							  Key bomb = KEY_E,
							  Key pause = RAY::Controller::Keyboard::Key::KEY_ESCAPE);

			//! @brief A Keyboard component is copy constructable.
			KeyboardComponent(const KeyboardComponent &) = default;

			//! @brief default destructor
			~KeyboardComponent() override = default;

			//! @brief A Keyboard component can't be assigned
			KeyboardComponent &operator=(const KeyboardComponent &) = delete;
	};
}