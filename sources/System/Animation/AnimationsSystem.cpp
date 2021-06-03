//
// Created by cbihan on 01/06/2021.
//

#include <iostream>
#include "AnimationsSystem.hpp"
#include "Component/Animation/AnimationsComponent.hpp"
#include "Model/Model.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"

namespace BBM
{

	AnimationsSystem::AnimationsSystem()
		: WAL::System({
			typeid(Drawable3DComponent<RAY::Drawables::Drawables3D::Model>),
			typeid(AnimationsComponent)
		})
	{
	}

	void AnimationsSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds)
	{
		auto &model = entity.getComponent<Drawable3DComponent<RAY::Drawables::Drawables3D::Model>>();
		auto &anim = entity.getComponent<AnimationsComponent>();

		if (anim.isDisabled())
			return;
		model.member.setAnimation(anim.getCurrentModelAnim());
		anim.incCurrentAnimFrameCounter();
	}
}