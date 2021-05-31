//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "GamepadSystem.hpp"
#include "Component/Gamepad/GamepadComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"
#include "Controllers/Gamepad.hpp"

using Button = RAY::Controller::GamePad::Button;
using Gamepad = RAY::Controller::GamePad;

namespace BBM
{
	GamepadSystem::GamepadSystem()
		: WAL::System({
			typeid(GamepadComponent),
			typeid(ControllableComponent)
		})
	{}

	void GamepadSystem::onFixedUpdate(WAL::Entity &entity)
	{
		const auto &gamepadComponent = entity.getComponent<GamepadComponent>();
		auto &controllable = entity.getComponent<ControllableComponent>();
		Gamepad gamepad(gamepadComponent.getID());

		const std::map<Button, bool> keyPressedMap = {
			{gamepadComponent.keyJump, controllable.jump},
			{gamepadComponent.keyBomb, controllable.bomb},
			{gamepadComponent.keyPause, controllable.pause}
		};

		for (auto key : keyPressedMap)
			key.second = gamepad.isPressed(key.first);
		controllable.moveX = 0;
		controllable.moveZ = 0;
		controllable.moveX += gamepad.isPressed(gamepadComponent.keyRight);
		controllable.moveX -= gamepad.isPressed(gamepadComponent.keyLeft);
		controllable.moveX += gamepad.isPressed(gamepadComponent.keyUp);
		controllable.moveX -= gamepad.isPressed(gamepadComponent.keyDown);
	}
}