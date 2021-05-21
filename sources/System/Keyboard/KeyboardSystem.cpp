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
		static const std::map<int, bool> keyPressedMap = {
			{keyboard.keyJump, controllable._jump},
			{keyboard.keyBomb, controllable._bomb},
			{keyboard.keyPause, controllable._pause}
		};

		for (auto key : keyPressedMap)
			key.second = RAY::IsKeyPressed(key.first);
		controllable._moveX = 0;
		controllable._moveZ = 0;
		if (RAY::IsKeyPressed(keyboard.keyRight))
			controllable._moveX += 1;
		if (RAY::IsKeyPressed(keyboard.keyLeft))
			controllable._moveX -= 1;
		if (RAY::IsKeyPressed(keyboard.keyUp))
			controllable._moveX += 1;
		if (RAY::IsKeyPressed(keyboard.keyDown))
			controllable._moveX -= 1;
	}
}