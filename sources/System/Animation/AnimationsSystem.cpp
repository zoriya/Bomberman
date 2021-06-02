//
// Created by cbihan on 01/06/2021.
//

#include "AnimationsSystem.hpp"
#include "Component/Animation/AnimationsComponent.hpp"
#include "Model/Model.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"

namespace BBM
{

	AnimationsSystem::AnimationsSystem()
		: WAL::System({typeid(AnimationsComponent),
				 typeid(Drawable3DComponent<RAY::Drawables::Drawables3D::Model>)})
	{
	}

	void AnimationsSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &model = entity.getComponent<Drawable3DComponent<RAY::Drawables::Drawables3D::Model>>();
		auto &anim = entity.getComponent<AnimationsComponent>();

		model.member.setAnimation(anim.getCurrentModelAnim());
		anim.setCurrentAnimFrameCounter(anim.getCurrentAnimFrameCounter() + 1);
	}
}