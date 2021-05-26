//
// Created by cbihan on 26/05/2021.
//

#pragma once

#include "System/System.hpp"
#include "Camera/Camera2D.hpp"
#include "Window.hpp"

namespace BBM
{
	template <class  T>
	class RenderScreenSystem : public WAL::System
	{
		//! @brief The window to render on
		RAY::Window &_window;
		//! @brief The camera
		T &_camera;
	public:
		//! @brief ctor
		explicit RenderScreenSystem(RAY::Window &window, T &camera)
			: WAL::System({typeid(RenderScreenSystem)}),
			  _window(window),
			  _camera(camera)
		{
		}

		//! @brief A method called after all entities that this system manage has been updated.
		//! @note render on screen here
		void onSelfUpdate() override
		{
			std::cout << "render" << std::endl;
			this->_window.unuseCamera();
			this->_window.setDrawingState(RAY::Window::IDLE);
			this->_camera.update();
			this->_window.setDrawingState(RAY::Window::DRAWING);
			this->_window.clear();
			this->_window.useCamera(_camera);
		}

		//! @brief Default copy ctor
		RenderScreenSystem(const RenderScreenSystem &) = default;
		//! @brief Default dtor
		~RenderScreenSystem() override = default;
		//! @brief Default assignment operator
		RenderScreenSystem &operator=(const RenderScreenSystem &) = default;

	};

}
