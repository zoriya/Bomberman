//
// Created by Zoe Roux on 6/9/21.
//

#include <Component/BombHolder/BombHolderComponent.hpp>
#include "BombSystem.hpp"

namespace BBM
{
	BombSystem::BombSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void BombSystem::onUpdate(WAL::ViewEntity<BasicBombComponent, PositionComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &bomb = entity.get<BasicBombComponent>();

		if (bomb.ignoredEntities.empty())
			return;

		auto &pos = entity.get<PositionComponent>();
		for (auto &[owner, ownerPos, _] : this->_wal.getScene()->view<PositionComponent, BombHolderComponent>()) {
			if (pos.position.distance(ownerPos.position) >= 1.1) {
				bomb.ignoredEntities.erase(
					std::remove(bomb.ignoredEntities.begin(), bomb.ignoredEntities.end(), owner.getUid()),
					bomb.ignoredEntities.end());
			}
		}
	}
}
