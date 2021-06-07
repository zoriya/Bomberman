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
		const std::vector<std::vector<float>> moveDiag = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
		const std::vector<float> rotationAngle = {0.0f, 45.0f, 90.0f, 135.0f, 180.0f, 225.0f, 270.0f, 315.0f};
		const auto &controllable = entity.getComponent<ControllableComponent>();
		auto drawable = entity.getComponent<Drawable3DComponent>().drawable.get();
		auto &animation = entity.getComponent<AnimationsComponent>();
		auto anim = dynamic_cast<RAY3D::Model *>(drawable);
		for (int i = 0; i != moveDiag.size(); i++) {
			if (controllable.move.x == moveDiag[i][0] && controllable.move.y == moveDiag[i][1]) {
				if (anim)
					anim->setRotationAngle(rotationAngle[i]);
				animation.setAnimIndex(0);
				return;
			}
		}
		animation.setAnimIndex(1);
	}
}