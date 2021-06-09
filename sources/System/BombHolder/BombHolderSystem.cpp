//
// Created by Zoe Roux on 5/31/21.
//

#include <Component/Animation/AnimationsComponent.hpp>
#include "Component/Timer/TimerComponent.hpp"
#include "System/Event/EventSystem.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "BombHolderSystem.hpp"
#include "Component/Health/HealthComponent.hpp"
#include <functional>
#include <Map/Map.hpp>
#include "Component/Collision/CollisionComponent.hpp"
#include "Component/Tag/TagComponent.hpp"

using namespace std::chrono_literals;
namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	std::chrono::nanoseconds BombHolderSystem::explosionTimer = 3s;

	BombHolderSystem::BombHolderSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void BombHolderSystem::_dispatchExplosion(Vector3f position, WAL::Wal &wal, int count)
	{
		if (count <= 0)
			return;
		wal.scene->scheduleNewEntity("explosion")
			.addComponent<PositionComponent>(position)
			.addComponent<TimerComponent>(1s, [](WAL::Entity &explosion, WAL::Wal &wal) {
				explosion.scheduleDeletion();
			})
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/bombs/explosion/explosion.glb",
															 std::make_pair(MAP_DIFFUSE, "assets/bombs/explosion/blast.png"));
		wal.getSystem<EventSystem>().dispatchEvent([position, count](WAL::Wal &wal) {
			for (auto &[entity, pos, _] : wal.scene->view<PositionComponent, TagComponent<Blowable>>()) {
				if (pos.position.round() == position) {
					if (auto *health = entity.tryGetComponent<HealthComponent>())
						health->takeDmg(1);
					return;
				}
			}
			_dispatchExplosion(position + Vector3f(1, 0, 0), wal, count - 1);
			_dispatchExplosion(position + Vector3f(-1, 0, 0), wal, count - 1);
			_dispatchExplosion(position + Vector3f(0, 0, 1), wal, count - 1);
			_dispatchExplosion(position + Vector3f(0, 0, -1), wal, count - 1);
		});
	}

	void BombHolderSystem::_bombExplosion(WAL::Entity &bomb, WAL::Wal &wal)
	{
		bomb.scheduleDeletion();
		auto position = bomb.getComponent<PositionComponent>().position.round();
		_dispatchExplosion(position, wal, 3);
	}

	void BombHolderSystem::_spawnBomb(Vector3f position)
	{
		this->_wal.scene->scheduleNewEntity("Bomb")
			.addComponent<PositionComponent>(position.round())
			.addComponent<TimerComponent>(BombHolderSystem::explosionTimer, &BombHolderSystem::_bombExplosion)
//			.addComponent<CollisionComponent>(WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
//			                                  &MapGenerator::wallCollide, 0.25, .75)
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