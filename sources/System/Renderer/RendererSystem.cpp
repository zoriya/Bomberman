//
// Created by cbihan on 24/05/2021.
//

#include "RendererSystem.hpp"
#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"

namespace BBM
{

	void RendererSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime)
	{
		WAL::System::onUpdate(entity, dtime);
	}

	void RendererSystem::onFixedUpdate(WAL::Entity &entity)
	{
		WAL::System::onFixedUpdate(entity);
	}

	void RendererSystem::onSelfUpdate()
	{
		WAL::System::onSelfUpdate();
	}

	RendererSystem::RendererSystem()
		: System({
			typeid(PositionComponent)
		})
	{
	}
}