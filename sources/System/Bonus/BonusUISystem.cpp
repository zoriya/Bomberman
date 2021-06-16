//
// Created by hbenjamin on 09/06/2021.
//

#include "BonusUISystem.hpp"

namespace BBM
{
	BonusUISystem::BonusUISystem(WAL::Wal &wal)
		: System(wal)
	{}

	void BonusUISystem::onFixedUpdate(WAL::ViewEntity<StatComponent, Drawable2DComponent> &entity)
	{
		entity.get<StatComponent>().updater(entity.get<Drawable2DComponent>());
	}
}