//
// Created by cbihan on 15/06/2021.
//

#include "ShaderDrawable2DSystem.hpp"

namespace BBM
{
	ShaderDrawable2DSystem::ShaderDrawable2DSystem(WAL::Wal &wal)
		: System(wal)
	{
	}

	void ShaderDrawable2DSystem::onFixedUpdate(WAL::ViewEntity<ShaderComponentDrawable2D> &entity)
	{
		auto &shader = entity->getComponent<ShaderComponentDrawable2D>();

		shader.onFixedUpdate(entity, this->_wal);
	}
}