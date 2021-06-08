//
// Created by hbenjamin on 07/06/2021.
//

#include "BombAnimatorSystem.hpp"
#include <Component/Animator/AnimatorComponent.hpp>
#include <Component/Animation/AnimationsComponent.hpp>

namespace BBM
{
	BombAnimatorSystem::BombAnimatorSystem(WAL::Wal &wal)
			: System(wal)
	{}

	void BombAnimatorSystem::onUpdate(WAL::ViewEntity<BombAnimatorComponent, AnimationsComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &animator = entity.get<BombAnimatorComponent>();

		animator.nextAnimationRate -= dtime;
		if (animator.nextAnimationRate <= 0ns) {
			animator.nextAnimationRate = animator.animationRate;
			/*auto &animation = entity.get<AnimationsComponent>();
			auto ind = animation.getCurrentAnimIndex();
			animation.setAnimIndex(ind++);*/
		}
	}
}