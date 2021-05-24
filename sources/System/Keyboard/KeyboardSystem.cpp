//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "KeyboardSystem.hpp"
#include "sources/Component/Keyboard/KeyboardComponent.hpp"
#include "sources/Component/Controllable/ControllableComponent.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace Bomberman
{
	const std::type_info &KeyboardSystem::getComponent() const
	{
		return typeid(KeyboardComponent);
	}

	void KeyboardSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &keyboard = entity.getComponent<KeyboardComponent>();
		auto &controllable= entity.getComponent<ControllableComponent>();
		static const std::map<int, bool> keyPressedMap = {
			{keyboard.keyJump, controllable.jump},
			{keyboard.keyBomb, controllable.bomb},
			{keyboard.keyPause, controllable.pause}
		};

		for (auto key : keyPressedMap)
			key.second = RAY::IsKeyPressed(key.first);
		controllable.moveX = 0;
		controllable.moveZ = 0;
		if (RAY::IsKeyPressed(keyboard.keyRight))
			controllable.moveX += 1;
		if (RAY::IsKeyPressed(keyboard.keyLeft))
			controllable.moveX -= 1;
		if (RAY::IsKeyPressed(keyboard.keyUp))
			controllable.moveX += 1;
		if (RAY::IsKeyPressed(keyboard.keyDown))
			controllable.moveX -= 1;
	}
}