//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "KeyboardSystem.hpp"
#include "sources/Component/Keyboard/KeyboardComponent.hpp"
#include "sources/Component/Controllable/ControllableComponent.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace BBM
{
	const std::type_info &KeyboardSystem::getComponent() const
	{
		return typeid(KeyboardComponent);
	}

	void KeyboardSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &keyboard = entity.getComponent<KeyboardComponent>();
		auto &controllable= entity.getComponent<ControllableComponent>();

		if (RAY::IsKeyPressed(keyboard.keyRight))
			controllable._right = true;
		if (RAY::IsKeyPressed(keyboard.keyLeft))
			controllable._left = true;
		if (RAY::IsKeyPressed(keyboard.keyUp))
			controllable._up = true;
		if (RAY::IsKeyPressed(keyboard.keyDown))
			controllable._down = true;
		if (RAY::IsKeyPressed(keyboard.keyBomb))
			controllable._bomb = true;
		if (RAY::IsKeyPressed(keyboard.keyJump))
			controllable._jump = true;
		if (RAY::IsKeyPressed(keyboard.keyPause))
			controllable._pause = true;
	}
}