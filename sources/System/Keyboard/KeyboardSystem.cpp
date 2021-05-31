//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

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

	void KeyboardSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds)
	{
		const auto &keyboard = entity.getComponent<KeyboardComponent>();
		auto &controllable = entity.getComponent<ControllableComponent>();

		const std::map<KeyboardKey, bool &> keyPressedMap = {
			{keyboard.keyJump, controllable.jump},
			{keyboard.keyBomb, controllable.bomb},
			{keyboard.keyPause, controllable.pause}
		};

		for (auto key : keyPressedMap)
			key.second = Keyboard::isPressed(key.first);
		controllable.move = Vector2f();
		if (Keyboard::isDown(keyboard.keyRight))
			controllable.move.x += 1;
		if (Keyboard::isDown(keyboard.keyLeft))
			controllable.move.x -= 1;
		if (Keyboard::isDown(keyboard.keyUp))
			controllable.move.y += 1;
		if (Keyboard::isDown(keyboard.keyDown))
			controllable.move.y -= 1;
	}
}