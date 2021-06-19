//
// Created by cbihan on 01/06/2021.
//

#include "AnimationsSystem.hpp"
#include "Component/Animation/AnimationsComponent.hpp"
#include "Model/Model.hpp"
#include <iostream>
#include "Component/Tag/TagComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"

namespace BBM
{

	AnimationsSystem::AnimationsSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void AnimationsSystem::onUpdate(WAL::ViewEntity<Drawable3DComponent, AnimationsComponent> &entity, std::chrono::nanoseconds)
	{
		auto &anim = entity.get<AnimationsComponent>();

		if (anim.isAnimDisabled())
			return;
		anim.incCurrentAnimFrameCounter();
		anim.incCurrentAnimFrameCounter();
		if (this->animsToSkip <= 0) {
			auto &model = entity.get<Drawable3DComponent>();
			auto modelPtr = std::dynamic_pointer_cast<RAY::Drawables::Drawables3D::Model>(model.drawable);
			if (modelPtr) {
				modelPtr->setAnimation(anim.getCurrentModelAnim());
			}
		}
	}

	void AnimationsSystem::onSelfUpdate(std::chrono::nanoseconds)
	{
		this->maxAnimsToSkip = this->_wal.getScene()->view<AnimationsComponent, TagComponent<Player>, PositionComponent>().size() - 1;
		if (this->animsToSkip <= 0) {
			this->animsToSkip = this->maxAnimsToSkip + 1;
		}
		this->animsToSkip--;
	}
}