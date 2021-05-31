//
// Created by Zoe Roux on 5/27/21.
//

#pragma once

#include <System/System.hpp>
#include <Window.hpp>

namespace BBM
{
	class Render2DScreenSystem : public WAL::System
	{
		//! @brief The window to render on
		RAY::Window &_window;

		//! @brief The camera used to render.
		RAY::Camera::Camera2D _camera;
	public:
		//! @brief A method called after all entities that this system manage has been updated.
		//! @note render on screen here
		void onSelfUpdate() override;

		//! @brief ctor
		explicit Render2DScreenSystem(RAY::Window &window);
		//! @brief Default copy ctor
		Render2DScreenSystem(const Render2DScreenSystem &) = default;
		//! @brief Default dtor
		~Render2DScreenSystem() override = default;
		//! @brief A render screen system can't be assigned.
		Render2DScreenSystem &operator=(const Render2DScreenSystem &) = delete;
	};
}