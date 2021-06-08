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
#include "Component/Bonus/BonusComponent.hpp"
#include "Entity/Entity.hpp"
#include "Items/Bonus.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	HealthSystem::HealthSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void HealthSystem::_createBonus(Vector3f position, BonusComponent::BonusType bonusType, std::chrono::nanoseconds timer)
	{
		static std::map<BonusComponent::BonusType, std::string> map = {
				{BonusComponent::BonusType::BOMBSTOCK, "assets/items/bombup"},
				{BonusComponent::BonusType::SPEEDUP, "assets/items/speedup"},
				//{BonusComponent::BonusType::EXPLOSIONINC, "assets/items/explosion"},
				{BonusComponent::BonusType::DAMAGEINC, "assets/items/fireup"},
				{BonusComponent::BonusType::IGNOREWALLS, "assets/items/wallpass"}
		};
		static std::vector<std::function<void (WAL::Entity &, const WAL::Entity &)>> func = {
				&Bonus::BombUpBonus, &Bonus::SpeedUpBonus, //&Bonus::ExplosionRangeBonus,
				&Bonus::DamageIncreasedBonus, &Bonus::IgnoreWallsBonus
		};

		if (bonusType == BonusComponent::BonusType::NOTHING)
			return;
		try {
			this->_wal.scene->scheduleNewEntity("Bonus")
					.addComponent<PositionComponent>(position)
					.addComponent<HealthComponent>(1, [](WAL::Entity &entity) {
						entity.scheduleDeletion();
					})
					.addComponent<LevitateComponent>(position.y)
					.addComponent<CollisionComponent>([](WAL::Entity &bonus, const WAL::Entity &player) {
						bonus.scheduleDeletion();
					}, func[bonusType - 1])
						.addComponent<TimerComponent>(timer, [](WAL::Entity &bonus, WAL::Wal &wal){
						  bonus.scheduleDeletion();
						})
					.addComponent<Drawable3DComponent, RAY3D::Model>(map.at(bonusType) + ".obj", std::make_pair(MAP_DIFFUSE, "assets/items/items.png"));
		} catch (std::out_of_range const &err) {}
	}

	void HealthSystem::onFixedUpdate(WAL::ViewEntity<HealthComponent, PositionComponent> &entity)
	{
		auto &health = entity.get<HealthComponent>();
		auto &position = entity.get<PositionComponent>();

		if (health.getHealthPoint() == 0) {
			if (entity->hasComponent<BonusComponent>()) {
				auto &bonus = entity->getComponent<BonusComponent>();
				auto bonusType = bonus.getRandomBonusType();
				this->_createBonus(position.position, bonusType, bonus.disappearTimer);
			}
			health.onDeath(entity);
		}
	}
}