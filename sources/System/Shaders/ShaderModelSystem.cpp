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

	void ShaderModelSystem::onUpdate(WAL::ViewEntity<ShaderComponentModel> &entity, std::chrono::nanoseconds dtime)
	{
		auto &shader = entity->getComponent<ShaderComponentModel>();

		shader.update(entity, this->_wal, dtime);
	}
}