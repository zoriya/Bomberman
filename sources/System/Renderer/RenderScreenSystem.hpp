//
// Created by cbihan on 26/05/2021.
//

#pragma once

#include "System/System.hpp"
#include "Camera/Camera2D.hpp"
#include "Window.hpp"

namespace BBM
{
	class RenderScreenSystem : public WAL::System
	{
		//! @brief The window to render on
		RAY::Window &_window;

		//! @brief The camera used to render.
		RAY::Camera::Camera3D _camera;
	public:
		//! @brief A method called after all entities that this system manage has been updated.
		//! @note render on screen here
		void onSelfUpdate() override;

		//! @inherit
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime) override;

		//! @brief ctor
		explicit RenderScreenSystem(RAY::Window &window);
		//! @brief Default copy ctor
		RenderScreenSystem(const RenderScreenSystem &) = default;
		//! @brief Default dtor
		~RenderScreenSystem() override = default;
		//! @brief A render screen system can't be assigned.
		RenderScreenSystem &operator=(const RenderScreenSystem &) = delete;
	};
}
