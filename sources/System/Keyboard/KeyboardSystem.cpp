//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include <iostream>
#include "KeyboardSystem.hpp"
#include "Component/Keyboard/KeyboardComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"
#include "Controllers/Keyboard.hpp"

using Keyboard = RAY::Controller::Keyboard;

namespace BBM
{
	KeyboardSystem::KeyboardSystem()
		: WAL::System({
			typeid(KeyboardComponent),
			typeid(ControllableComponent)
		})
	{}

	void KeyboardSystem::onFixedUpdate(WAL::Entity &entity)
	{
		const auto &keyboard = entity.getComponent<KeyboardComponent>();
		auto &controllable = entity.getComponent<ControllableComponent>();

		const std::map<KeyboardKey, bool &> keyPressedMap = {
			{keyboard.keyJump, controllable.jump},
			{keyboard.keyBomb, controllable.bomb},
			{keyboard.keyPause, controllable.pause}
		};

		for (auto key : keyPressedMap)
			key.second = Keyboard::isDown(key.first);
		controllable.moveX = 0;
		controllable.moveZ = 0;
		if (Keyboard::isDown(keyboard.keyRight))
			controllable.moveX += 1;
		if (Keyboard::isDown(keyboard.keyLeft))
			controllable.moveX -= 1;
		if (Keyboard::isDown(keyboard.keyUp))
			controllable.moveZ += 1;
		if (Keyboard::isDown(keyboard.keyDown))
			controllable.moveZ -= 1;
	}
}