//
// Created by hbenjamin on 07/06/2021.
//

#include "LevitateSystem.hpp"

namespace BBM {
	LevitateSystem::LevitateSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void LevitateSystem::onFixedUpdate(WAL::ViewEntity<LevitateComponent, PositionComponent> &entity) {
		auto &levitate = entity.get<LevitateComponent>();
		auto &position = entity.get<PositionComponent>();
		float &y = position.position.y;

		if (levitate.up) {
			if (y < levitate.y + 0.1f)
				y += 0.004f;
			else
				levitate.up = false;
			return;
		}
		if (y > levitate.y - 0.1f)
			y -= 0.004f;
		else
			levitate.up = true;
	}
}