//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "System/System.hpp"
#include "RendererSystem.hpp"
#include "Entity/Entity.hpp"
#include "Window.hpp"

namespace BBM
{

	class RectangleDrawable2DSystem : public RendererSystem
	{
	public:
		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		//! @param dtime The delta time.
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime) override;

		explicit RectangleDrawable2DSystem(RAY::Window &w);
		RectangleDrawable2DSystem(const RectangleDrawable2DSystem &) = default;
		~RectangleDrawable2DSystem() override = default;
		RectangleDrawable2DSystem &operator=(const RectangleDrawable2DSystem &) = default;
	};

}
