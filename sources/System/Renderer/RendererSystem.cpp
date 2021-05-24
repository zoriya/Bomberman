//
// Created by cbihan on 24/05/2021.
//

#include "RendererSystem.hpp"
#include "Component/Position/PositionComponent.hpp"

namespace WAL
{

	void RendererSystem::onUpdate(Entity &entity, std::chrono::nanoseconds dtime)
	{
		System::onUpdate(entity, dtime);
	}

	void RendererSystem::onFixedUpdate(Entity &entity)
	{
		System::onFixedUpdate(entity);
	}

	void RendererSystem::onSelfUpdate()
	{
		System::onSelfUpdate();
	}

	RendererSystem::RendererSystem()
		: System({
			typeid(PositionComponent)
		})
	{
	}
}