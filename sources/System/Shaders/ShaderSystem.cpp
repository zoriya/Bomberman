//
// Created by cbihan on 15/06/2021.
//

#include "ShaderSystem.hpp"


namespace BBM
{
	ShaderSystem::ShaderSystem(WAL::Wal &wal)
		: System(wal)
	{
	}

	void ShaderSystem::onFixedUpdate(WAL::ViewEntity<ShaderComponent> &entity)
	{
		auto &shader = entity->getComponent<ShaderComponent>();

		shader.onFixedUpdate(entity, this->_wal);
	}
}