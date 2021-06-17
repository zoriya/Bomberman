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
	AnimatorSystem::AnimatorSystem(WAL::Wal &wal)
			: System(wal)
	{}

	void AnimatorSystem::onFixedUpdate(WAL::ViewEntity<AnimationsComponent, ControllableComponent, Drawable3DComponent> &entity)
	{
		const auto &controllable = entity.get<ControllableComponent>();
		auto drawable = entity.get<Drawable3DComponent>().drawable.get();
		auto &animation = entity.get<AnimationsComponent>();
		auto anim = dynamic_cast<RAY3D::Model *>(drawable);

		if (entity->shouldDelete())
			return;
		if (anim && controllable.move != Vector2f(0, 0)) {
			anim->setRotationAngle(controllable.move.angle(Vector2f(-1, 0)));
			animation.setAnimIndex(0);
			return;
		}
		animation.setAnimIndex(1);
	}
}