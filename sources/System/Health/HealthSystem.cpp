//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include <Component/Animation/AnimationsComponent.hpp>
#include "HealthSystem.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	HealthSystem::HealthSystem()
		: WAL::System({
			typeid(HealthComponent),
			typeid(AnimationsComponent)
		})
	{}

	void HealthSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &health = entity.getComponent<HealthComponent>();

		if (health.getHealthPoint() == 0) {
			if (entity.hasComponent<AnimationsComponent>()) {
				auto &animation = entity.getComponent<AnimationsComponent>();
				animation.setAnimIndex(5);
			}
			health.onDeath(entity);
		}
	}
}