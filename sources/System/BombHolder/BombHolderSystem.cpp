//
// Created by Zoe Roux on 5/31/21.
//

#include "Component/Timer/TimerComponent.hpp"
#include "System/Event/EventSystem.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "BombHolderSystem.hpp"
#include "Component/Health/HealthComponent.hpp"

using namespace std::chrono_literals;
namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	std::chrono::nanoseconds BombHolderSystem::explosionTimer = 3s;
	float BombHolderSystem::explosionRadius = 3;

	BombHolderSystem::BombHolderSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void BombHolderSystem::_bombExplosion(WAL::Entity &bomb, WAL::Wal &wal)
	{
		bomb.scheduleDeletion();
		auto &bombPosition = bomb.getComponent<PositionComponent>();
		wal.getSystem<EventSystem>().dispatchEvent([&bombPosition](WAL::Entity &entity){
			auto *health = entity.tryGetComponent<HealthComponent>();
			auto *pos = entity.tryGetComponent<PositionComponent>();

			if (!health || !pos)
				return;
			if (pos->position.distance(bombPosition.position) > BombHolderSystem::explosionRadius)
				return;
			// TODO do a raycast here to only remove health to entities that are not behind others.
			health->takeDmg(1);
		});
	}

	void BombHolderSystem::_spawnBomb(Vector3f position)
	{
		this->_wal.scene->scheduleNewEntity("Bomb")
			.addComponent<PositionComponent>(position)
			.addComponent<TimerComponent>(BombHolderSystem::explosionTimer, &BombHolderSystem::_bombExplosion)
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/bombs/bomb.obj",
				std::make_pair(MAP_DIFFUSE, "assets/bombs/bomb_normal.png"));
	}

	void BombHolderSystem::onUpdate(WAL::ViewEntity<PositionComponent, BombHolderComponent, ControllableComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &holder = entity.get<BombHolderComponent>();
		auto &position = entity.get<PositionComponent>();
		auto &controllable = entity.get<ControllableComponent>();

		if (controllable.bomb && holder.bombCount > 0) {
			holder.bombCount--;
			this->_spawnBomb(position.position);
		}
		if (holder.bombCount < holder.maxBombCount) {
			holder.nextBombRefill -= dtime;
			if (holder.nextBombRefill <= 0ns) {
				holder.nextBombRefill = holder.refillRate;
				holder.bombCount++;
			}
		}
	}
}