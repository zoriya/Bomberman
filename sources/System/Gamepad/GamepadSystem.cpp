//
// Created by Arthur Jamet on 2021-05-31.
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
	GamepadSystem::GamepadSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void GamepadSystem::onUpdate(WAL::ViewEntity<GamepadComponent, ControllableComponent> &entity, std::chrono::nanoseconds)
	{
		const auto &gamepadComponent = entity.get<GamepadComponent>();
		auto &controllable = entity.get<ControllableComponent>();

		if (controllable.disabled)
			return;

		Gamepad gamepad(gamepadComponent.getID());
		const std::map<Button, bool &> keyPressedMap = {
			{gamepadComponent.keySecondary, controllable.secondary},
			{gamepadComponent.keyBomb,      controllable.bomb},
			{gamepadComponent.keyPause,     controllable.pause}
		};

		for (auto key : keyPressedMap)
			key.second = controllable.fastClick ? gamepad.isDown(key.first) : gamepad.isPressed(key.first);
		if (gamepad.isPressed(GAMEPAD_BUTTON_MIDDLE_LEFT) || gamepad.isPressed(GAMEPAD_BUTTON_MIDDLE_RIGHT))
			controllable.pause = true;
		controllable.move.x = gamepad.getAxisValue(gamepadComponent.LeftStickX) * -1;
		controllable.move.y = gamepad.getAxisValue(gamepadComponent.LeftStickY) * -1;
		controllable.move.x -= static_cast<float>(gamepad.isDown(gamepadComponent.keyRight));
		controllable.move.x += static_cast<float>(gamepad.isDown(gamepadComponent.keyLeft));
		controllable.move.y += static_cast<float>(gamepad.isDown(gamepadComponent.keyUp));
		controllable.move.y -= static_cast<float>(gamepad.isDown(gamepadComponent.keyDown));
	}
}