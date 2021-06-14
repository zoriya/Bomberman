//
// Created by Zoe Roux on 5/31/21.
//

#include <Component/Animation/AnimationsComponent.hpp>
#include <Component/Bomb/BasicBombComponent.hpp>
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
	std::chrono::nanoseconds BombHolderSystem::explosionTimer = 2s;

	void BombHolderSystem::_bombCollide(WAL::Entity &entity,
	                                    const WAL::Entity &bomb,
	                                    CollisionComponent::CollidedAxis collidedAxis)
	{
		auto &bombInfo = bomb.getComponent<BasicBombComponent>();
		if (bombInfo.ignoreOwner && bombInfo.ownerID == entity.getUid())
			return;
		return MapGenerator::wallCollided(entity, bomb, collidedAxis);
	}

	BombHolderSystem::BombHolderSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void BombHolderSystem::_dispatchExplosion(const Vector3f &position,
	                                          WAL::Wal &wal,
	                                          int radiusToDo,
	                                          ExpansionDirection expansionDirections)
	{
		if (radiusToDo <= 0)
			return;
		wal.getScene()->scheduleNewEntity("explosion")
			.addComponent<PositionComponent>(position)
			.addComponent<TimerComponent>(1s, [](WAL::Entity &explosion, WAL::Wal &wal) {
				explosion.scheduleDeletion();
			})
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/bombs/explosion/explosion.glb", false,
			                                                 std::make_pair(
				                                                 MAP_DIFFUSE,
				                                                 "assets/bombs/explosion/blast.png"
			                                                 ));
		wal.getSystem<EventSystem>().dispatchEvent([position, radiusToDo, expansionDirections](WAL::Wal &wal) {
			for (auto &[entity, pos, _] : wal.getScene()->view<PositionComponent, TagComponent<Blowable>>()) {
				if (pos.position.round() == position) {
					if (auto *health = entity.tryGetComponent<HealthComponent>())
						health->takeDmg(1);
					return;
				}
			}
			if (expansionDirections & ExpansionDirection::FRONT) {
				_dispatchExplosion(position + Vector3f{1, 0, 0}, wal, radiusToDo - 1, ExpansionDirection::FRONT);
			}
			if (expansionDirections & ExpansionDirection::BACK) {
				_dispatchExplosion(position + Vector3f{-1, 0, 0}, wal, radiusToDo - 1, ExpansionDirection::BACK);
			}
			if (expansionDirections & ExpansionDirection::LEFT) {
				_dispatchExplosion(position + Vector3f{0, 0, 1}, wal, radiusToDo - 1, ExpansionDirection::LEFT);
			}
			if (expansionDirections & ExpansionDirection::RIGHT) {
				_dispatchExplosion(position + Vector3f{0, 0, -1}, wal, radiusToDo - 1, ExpansionDirection::RIGHT);
			}
		});
	}

	void BombHolderSystem::_bombExplosion(WAL::Entity &bomb, WAL::Wal &wal)
	{
		bomb.scheduleDeletion();
		auto position = bomb.getComponent<PositionComponent>().position.round();
		auto explosionRadius = bomb.getComponent<BasicBombComponent>().explosionRadius;
		_dispatchExplosion(position, wal, explosionRadius);
	}

	void BombHolderSystem::_spawnBomb(Vector3f position, BombHolderComponent &holder, unsigned id)
	{
		this->_wal.getScene()->scheduleNewEntity("Bomb")
			.addComponent<PositionComponent>(position.round())
			.addComponent<BasicBombComponent>(holder.damage, holder.explosionRadius, id)
			.addComponent<TimerComponent>(BombHolderSystem::explosionTimer, &BombHolderSystem::_bombExplosion)
			.addComponent<CollisionComponent>(
				WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
				&BombHolderSystem::_bombCollide, 0.25, .75)
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/bombs/bomb.obj", false,
			                                                 std::make_pair(
				                                                 MAP_DIFFUSE,
				                                                 "assets/bombs/bomb_normal.png"
			                                                 ));
		holder.damage = 1;
		holder.explosionRadius = 3;
	}

	void
	BombHolderSystem::onUpdate(WAL::ViewEntity<PositionComponent, BombHolderComponent, ControllableComponent> &entity,
	                           std::chrono::nanoseconds dtime)
	{
		auto &holder = entity.get<BombHolderComponent>();
		auto &position = entity.get<PositionComponent>();
		auto &controllable = entity.get<ControllableComponent>();

		if (controllable.bomb && holder.bombCount > 0) {
			holder.bombCount--;
			this->_spawnBomb(position.position, holder, entity->getUid());
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