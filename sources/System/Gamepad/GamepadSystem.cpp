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

	void GamepadSystem::onFixedUpdate(WAL::ViewEntity<GamepadComponent, ControllableComponent> &entity)
	{
		const auto &gamepadComponent = entity.get<GamepadComponent>();
		auto &controllable = entity.get<ControllableComponent>();
		Gamepad gamepad(gamepadComponent.getID());

		const std::map<Button, bool &> keyPressedMap = {
			{gamepadComponent.keyJump, controllable.jump},
			{gamepadComponent.keyBomb, controllable.bomb},
			{gamepadComponent.keyPause, controllable.pause}
		};

		for (auto key : keyPressedMap)
			key.second = gamepad.isDown(key.first);
		controllable.move.x = gamepad.getAxisValue(gamepadComponent.LeftStickX) * -1;
		controllable.move.y = gamepad.getAxisValue(gamepadComponent.LeftStickY) * -1;
		controllable.move.x -= static_cast<float>(gamepad.isDown(gamepadComponent.keyRight));
		controllable.move.x += static_cast<float>(gamepad.isDown(gamepadComponent.keyLeft));
		controllable.move.y += static_cast<float>(gamepad.isDown(gamepadComponent.keyUp));
		controllable.move.y -= static_cast<float>(gamepad.isDown(gamepadComponent.keyDown));
	}
}