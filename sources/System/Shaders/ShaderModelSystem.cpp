//
// Created by cbihan on 15/06/2021.
//

#include "ShaderModelSystem.hpp"

namespace BBM
{
	ShaderModelSystem::ShaderModelSystem(WAL::Wal &wal)
		: System(wal)
	{
	}

	void ShaderModelSystem::onFixedUpdate(WAL::ViewEntity<ShaderComponentModel> &entity)
	{
		auto &shader = entity->getComponent<ShaderComponentModel>();

		shader.onFixedUpdate(entity, this->_wal);
	}
}