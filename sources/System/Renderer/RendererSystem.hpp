//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "System/System.hpp"
#include "Entity/Entity.hpp"
#include "Window.hpp"

namespace BBM
{
	class RendererSystem : public WAL::System
	{
	protected:
		//! @brief The window to render on
		RAY::Window &_w;
	public:
		RendererSystem(RAY::Window &window);
		RendererSystem(const RendererSystem &) = default;
		~RendererSystem() override = default;
		RendererSystem &operator=(const RendererSystem &) = delete;
	};
}