//
// Created by Zoe Roux on 6/9/21.
//

#include "BombSystem.hpp"

namespace BBM
{
	BombSystem::BombSystem(WAL::Wal &wal)
		: System(wal)
	{

	}

	void BombSystem::onUpdate(WAL::ViewEntity<BasicBombComponent> &entity, std::chrono::nanoseconds dtime)
	{
//		if (entity.get<BasicBombComponent>().)
		// TODO set ignoreOwner to false once the player moved out of the block.
	}
}
