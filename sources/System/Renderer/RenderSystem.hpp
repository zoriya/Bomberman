//
// Created by cbihan on 26/05/2021.
//

#pragma once

#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
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

		//! @brief Defines if the debug informations must be displayed or not
		bool _debugMode;

		//! @brief Window framerate limit
		static constexpr short FPS = 60;

	public:
		//! @brief A method called after all entities that this system manage has been updated.
		//! @note render on screen here
		void onSelfUpdate() override;

		//! @inherit
		void onUpdate(WAL::ViewEntity<CameraComponent, PositionComponent> &entity, std::chrono::nanoseconds dtime) override;

		//! @param debug true if debug mode should be enabled
		void setDebug(bool debug);

		//! @param entity entity to draw bounding box of
		void drawBoundingBox(const WAL::Entity &entity, const PositionComponent &posComponent, const Drawable3DComponent &drawable) const;

		//! @brief ctor
		RenderSystem(WAL::Wal &wal, RAY::Window &window, bool debugMode = false);
		//! @brief Default copy ctor
		RenderSystem(const RenderSystem &) = default;
		//! @brief Default dtor
		~RenderSystem() override = default;
		//! @brief A render screen system can't be assigned.
		RenderSystem &operator=(const RenderSystem &) = delete;
	};
}
