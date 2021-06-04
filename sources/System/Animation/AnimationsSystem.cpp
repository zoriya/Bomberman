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
			typeid(Drawable3DComponent),
			typeid(AnimationsComponent)
		})
	{
	}

	void AnimationsSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds)
	{
		auto &model = entity.getComponent<Drawable3DComponent>();
		auto &anim = entity.getComponent<AnimationsComponent>();

		if (anim.isDisabled())
			return;
		auto modelPtr = std::dynamic_pointer_cast<RAY::Drawables::Drawables3D::Model>(model.drawable);
		if (modelPtr) {
			modelPtr->setAnimation(anim.getCurrentModelAnim());
			anim.incCurrentAnimFrameCounter();
		}
	}
}