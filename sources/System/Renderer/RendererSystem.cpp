//
// Created by cbihan on 24/05/2021.
//

#include "RendererSystem.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Window.hpp"

namespace BBM
{
	RendererSystem::RendererSystem(RAY::Window &window)
		: System({
			typeid(PositionComponent)
		}),
		_w(window)
	{
	}
}