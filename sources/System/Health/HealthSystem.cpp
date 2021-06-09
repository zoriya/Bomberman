//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include <Component/Position/PositionComponent.hpp>
#include <Component/Renderer/Drawable3DComponent.hpp>
#include <map>
#include <Component/Levitate/LevitateComponent.hpp>
#include "Component/Collision/CollisionComponent.hpp"
#include <Component/Animation/AnimationsComponent.hpp>
#include <Component/Timer/TimerComponent.hpp>
#include "HealthSystem.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Entity/Entity.hpp"
#include "Items/Bonus.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	HealthSystem::HealthSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void HealthSystem::onFixedUpdate(WAL::ViewEntity<HealthComponent, PositionComponent> &entity)
	{
		auto &health = entity.get<HealthComponent>();
		auto &position = entity.get<PositionComponent>();

		if (health.getHealthPoint() == 0) {
			health.onDeath(entity, this->_wal);
		}
	}
}