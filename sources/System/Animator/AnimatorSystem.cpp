//
// Created by hbenjamin on 03/06/2021.
//

#include <Component/Animator/AnimatorComponent.hpp>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <Controllers/Keyboard.hpp>
#include <Model/Model.hpp>
#include <Component/Animation/AnimationsComponent.hpp>
#include <Component/Controllable/ControllableComponent.hpp>
#include "AnimatorSystem.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"

using Keyboard = RAY::Controller::Keyboard;
namespace RAY3D = RAY::Drawables::Drawables3D;
using Key = RAY::Controller::Keyboard::Key;

namespace BBM
{
	AnimatorSystem::AnimatorSystem()
			: WAL::System({
				typeid(AnimatorComponent),
				typeid(ControllableComponent)
			})
	{}

	void AnimatorSystem::onFixedUpdate(WAL::Entity &entity)
	{
		if (!entity.hasComponent<ControllableComponent>())
			return;
		const auto &controllable = entity.getComponent<ControllableComponent>();
		auto &model = entity.getComponent<Drawable3DComponent<RAY3D::Model>>();
		auto &animation = entity.getComponent<AnimationsComponent>();
		if (controllable.move.x == 1) {
			model.member.setRotationAngle(180.0f);
			animation.setAnimIndex(0);
			return;
		}
		if (controllable.move.x == -1) {
			model.member.setRotationAngle(0.0f);
			animation.setAnimIndex(0);
			return;
		}
		if (controllable.move.y == 1) {
			model.member.setRotationAngle(90.0f);
			animation.setAnimIndex(0);
			return;
		}
		if (controllable.move.y == -1) {
			model.member.setRotationAngle(270.0f);
			animation.setAnimIndex(0);
			return;
		}
		animation.setAnimIndex(1);
	}
}