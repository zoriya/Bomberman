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

		const std::map<Button, bool &> keyPressedMap = {
			{gamepadComponent.keyJump, controllable.jump},
			{gamepadComponent.keyBomb, controllable.bomb},
			{gamepadComponent.keyPause, controllable.pause}
		};

		for (auto key : keyPressedMap)
			key.second = gamepad.isPressed(key.first);
		controllable.move = Vector2f();
		controllable.move.x += gamepad.isPressed(gamepadComponent.keyRight);
		controllable.move.x -= gamepad.isPressed(gamepadComponent.keyLeft);
		controllable.move.y += gamepad.isPressed(gamepadComponent.keyUp);
		controllable.move.y -= gamepad.isPressed(gamepadComponent.keyDown);
	}
}