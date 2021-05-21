//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/Component/Component.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace BBM 
{
	class KeyboardComponent : public WAL::Component
	{
		public:

			//! @brief jump key
			int keyJump;
			//! @brief bomb key
			int keyBomb;
			//! @brief pause key
			int keyPause;
			//! @brief move right key
			int keyRight;
			//! @brief move left key
			int keyLeft;
			//! @brief move up key
			int keyUp;
			//! @brief move down key
			int keyDown;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief A Keyboard component can't be instantiated, it should be derived.
			explicit KeyboardComponent(WAL::Entity &entity);

			//! @brief Constructor
			KeyboardComponent(WAL::Entity &entity, unsigned int maxBombCount);

			//! @brief A Keyboard component can't be instantiated, it should be derived.
			KeyboardComponent(const KeyboardComponent &) = default;

			//! @brief default destructor
			~KeyboardComponent() override = default;

			//! @brief A Keyboard component can't be assigned
			KeyboardComponent &operator=(const KeyboardComponent &) = delete;
	};
}