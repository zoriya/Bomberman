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
		if (!bomb.ignoreOwner)
			return;
		auto &pos = entity.get<PositionComponent>();
		for (auto &[owner, ownerPos, _] : this->_wal.getScene()->view<PositionComponent, BombHolderComponent>()) {
			if (owner.getUid() != bomb.ownerID)
				continue;
			if (pos.position != ownerPos.position.round()) {
				bomb.ignoreOwner = false;
				return;
			}
		}
	}
}
