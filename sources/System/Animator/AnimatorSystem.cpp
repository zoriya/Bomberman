//
// Created by hbenjamin on 03/06/2021.
//

#include <Component/Animator/AnimatorComponent.hpp>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <Controllers/Keyboard.hpp>
#include <Model/Model.hpp>
#include <Component/Animation/AnimationsComponent.hpp>
#include "AnimatorSystem.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"

using Keyboard = RAY::Controller::Keyboard;
namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	AnimatorSystem::AnimatorSystem()
			: WAL::System({
				typeid(AnimatorComponent),
				typeid(KeyboardComponent)
			})
	{}

	void AnimatorSystem::onFixedUpdate(WAL::Entity &entity)
	{
		if (!entity.hasComponent<KeyboardComponent>())
			return;
		auto &model = entity.getComponent<Drawable3DComponent<RAY3D::Model>>();
		auto &animation = entity.getComponent<AnimationsComponent>();
		const auto &keyboard = entity.getComponent<KeyboardComponent>();
		animation.setAnimIndex(1);
		if (Keyboard::isDown(keyboard.keyRight)) {
			model.member.setRotationAngle(180.0f);
		}
		if (Keyboard::isDown(keyboard.keyLeft)) {
			model.member.setRotationAngle(0.0f);
		}
		if (Keyboard::isDown(keyboard.keyUp)) {
			model.member.setRotationAngle(90.0f);
		}
		if (Keyboard::isDown(keyboard.keyDown)) {
			model.member.setRotationAngle(270.0f);
		}
	}
}