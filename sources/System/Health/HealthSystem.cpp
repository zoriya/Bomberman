//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include <Component/Position/PositionComponent.hpp>
#include <Component/Renderer/Drawable3DComponent.hpp>
#include <map>
#include "Component/Collision/CollisionComponent.hpp"
#include "HealthSystem.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Component/Bonus/BonusComponent.hpp"
#include "Entity/Entity.hpp"
#include "Bonus/Bonus.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	HealthSystem::HealthSystem(WAL::Wal &wal)
		: WAL::System({
			typeid(HealthComponent)
		}),
		_wal(wal)
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
				&Bonus::BombUpBonus, &Bonus::SpeedUpBonus, &Bonus::ExplosionRangeBonus,
				&Bonus::DamageIncreasedBonus, &Bonus::IgnoreWallsBonus
		};

		if (bonusType == BonusComponent::BonusType::NOTHING)
		    return;
		std::cout << "Bonus spawned" << std::endl;
		this->_wal.scene->addEntity("Bonus")
			.addComponent<PositionComponent>(position)
			.addComponent<HealthComponent>(1)
			.addComponent<CollisionComponent>([](WAL::Entity &bonus, const WAL::Entity &player) {
					//bonus.scheduleDeletion(true);
				}, func[bonusType - 1])
			//.addComponent<TimerComponent>(timer, &[](WAL::Entity &bonus){
			//  std::cout << "Bonus disappeared" << std::endl;
			//  bonus.scheduleDeletion();
			// })
			.addComponent<Drawable3DComponent<RAY3D::Model>>(map.at(bonusType) + ".obj", std::make_pair(MAP_DIFFUSE, "assets/items/items.png"));
	}

	void HealthSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &health = entity.getComponent<HealthComponent>();
        auto &position = entity.getComponent<PositionComponent>();

		if (health.getHealthPoint() == 0) {
			if (entity.hasComponent<BonusComponent>()) {
				auto &bonus = entity.getComponent<BonusComponent>();
				auto bonusType = bonus.getRandomBonusType();
				this->_createBonus(position.position, bonusType, bonus.disappearTimer);
			}
			health.onDeath(entity);
		}
	}
}