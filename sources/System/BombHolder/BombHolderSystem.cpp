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
#include <Meshes/MeshSphere.hpp>
#include "Component/Shaders/Items/BombExplosionShaderComponent.hpp"
#include <chrono>
#include "Component/Shaders/ShaderComponent.hpp"
#include "Component/Collision/CollisionComponent.hpp"
#include "Component/Tag/TagComponent.hpp"
#include "Component/Shaders/Items/WhiteShaderComponent.hpp"

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
	                                          int size,
	                                          ExpansionDirection expansionDirections)
	{
		if (size <= 0)
			return;
		wal.getScene()->scheduleNewEntity("explosion")
			.addComponent<PositionComponent>(position)
		    .addComponent<BombExplosionShaderComponent>()
			.addComponent<ShaderComponentModel>("assets/shaders/explosion.fs", "assets/shaders/explosion.vs", [](WAL::Entity &entity, WAL::Wal &wal, std::chrono::nanoseconds dtime) {
				auto &ctx = entity.getComponent<BombExplosionShaderComponent>();
				auto &shader = entity.getComponent<ShaderComponentModel>();

				ctx.clock += dtime;
				if (duration_cast<std::chrono::milliseconds>(ctx.clock).count() <= 10)
					return;
				ctx.clock = 0ns;
				ctx.explosionRadius -= 0.6;
				if (ctx.explosionRadius < BombExplosionShaderComponent::maxRadius) {
					ctx.explosionRadius = BombExplosionShaderComponent::maxRadius;
					ctx.alpha -= 0.1;
					// slow the explosion movement
					ctx.frameCounter -= 0.1;
				}
				ctx.frameCounter += 0.2;
				shader.shader.setShaderUniformVar("frame", ctx.frameCounter);
				shader.shader.setShaderUniformVar("alpha", ctx.alpha);
				shader.shader.setShaderUniformVar("radius", ctx.explosionRadius);
			})
			.addComponent<TimerComponent>(500ms, [](WAL::Entity &explosion, WAL::Wal &wal) {
				explosion.scheduleDeletion();
			})
			.addComponent<Drawable3DComponent, RAY3D::Model>(RAY::Mesh::MeshSphere(0.5, 16, 16),
			                                                 std::make_pair(
				                                                 MAP_DIFFUSE,
				                                                 "assets/bombs/explosion/blast.png"
			                                                 ));
		wal.getSystem<EventSystem>().dispatchEvent([position, size, expansionDirections](WAL::Wal &wal) {
			for (auto &[entity, pos, _] : wal.getScene()->view<PositionComponent, TagComponent<Blowable>>()) {
				if (pos.position.round() == position) {
					if (auto *health = entity.tryGetComponent<HealthComponent>())
						health->takeDmg(1);
					return;
				}
			}
			for (auto &[entity, pos, _] : wal.getScene()->view<PositionComponent, TagComponent<BlowablePass>>()) {
				if (pos.position.round() == position) {
					if (auto *health = entity.tryGetComponent<HealthComponent>())
						health->takeDmg(1);
				}
			}
			if (expansionDirections & ExpansionDirection::FRONT) {
				_dispatchExplosion(position + Vector3f{1, 0, 0}, wal, size - 1, ExpansionDirection::FRONT);
			}
			if (expansionDirections & ExpansionDirection::BACK) {
				_dispatchExplosion(position + Vector3f{-1, 0, 0}, wal, size - 1, ExpansionDirection::BACK);
			}
			if (expansionDirections & ExpansionDirection::LEFT) {
				_dispatchExplosion(position + Vector3f{0, 0, 1}, wal, size - 1, ExpansionDirection::LEFT);
			}
			if (expansionDirections & ExpansionDirection::RIGHT) {
				_dispatchExplosion(position + Vector3f{0, 0, -1}, wal, size - 1, ExpansionDirection::RIGHT);
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
			.addComponent<HealthComponent>(1, [](WAL::Entity &entity, WAL::Wal &wal) {
				// the bomb explode when hit
				entity.scheduleDeletion();
				auto &pos = entity.getComponent<PositionComponent>();
				auto &bombDetails = entity.getComponent<BasicBombComponent>();
				BombHolderSystem::_dispatchExplosion(pos.position, wal, bombDetails.explosionRadius);
			})
			.addComponent<ShaderComponentModel>("assets/shaders/white.fs", "", [](WAL::Entity &entity, WAL::Wal &wal, std::chrono::nanoseconds dtime) {
				auto &ctx = entity.getComponent<WhiteShaderComponent>();
				auto &shader = entity.getComponent<ShaderComponentModel>();
				auto &timer = entity.getComponent<TimerComponent>();

				if (ctx.whiteValue >= 1)
					ctx.balance = -1;
				if (ctx.whiteValue <= 0)
					ctx.balance = 1;
				auto nbMilliSec = duration_cast<std::chrono::milliseconds>(timer.ringIn).count();

				float step;

				if (nbMilliSec > 1000) {
					step = 0.07;
				} else if (nbMilliSec > 500) {
					step = 0.15;
				} else if (nbMilliSec > 100) {
					step = 0.26;
				} else {
					step = 0.5;
				}

				ctx.whiteValue += static_cast<float>(step * ctx.balance);
				shader.shader.setShaderUniformVar("white", ctx.whiteValue);
			})
			.addComponent<WhiteShaderComponent>()
			.addComponent<TagComponent<BlowablePass>>()
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