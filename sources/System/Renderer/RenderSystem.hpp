//
// Created by cbihan on 26/05/2021.
//

#pragma once

#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "System/System.hpp"
#include "Camera/Camera2D.hpp"
#include "Window.hpp"
#include "Wal.hpp"

namespace BBM
{
	class RenderSystem : public WAL::System<CameraComponent, PositionComponent>
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
		void onUpdate(WAL::ViewEntity<CameraComponent, PositionComponent> &entity, std::chrono::nanoseconds dtime) override;

		//! @brief ctor
		RenderSystem(WAL::Wal &wal, RAY::Window &window);
		//! @brief Default copy ctor
		RenderSystem(const RenderSystem &) = default;
		//! @brief Default dtor
		~RenderSystem() override = default;
		//! @brief A render screen system can't be assigned.
		RenderSystem &operator=(const RenderSystem &) = delete;
	};
}