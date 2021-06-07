//
// Created by hbenjamin on 07/06/2021.
//

#include "LevitateSystem.hpp"

namespace BBM {
	LevitateSystem::LevitateSystem()
		: WAL::System({
			typeid(LevitateComponent),
			typeid(PositionComponent)
  		})
	{}

	void LevitateSystem::onFixedUpdate(WAL::Entity &entity) {
		auto &levitate = entity.getComponent<LevitateComponent>();
		auto &position = entity.getComponent<PositionComponent>();
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