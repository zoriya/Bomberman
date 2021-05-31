//
// Created by Zoe Roux on 5/27/21.
//

#include "Render2DScreenSystem.hpp"

namespace BBM
{
	Render2DScreenSystem::Render2DScreenSystem(RAY::Window &window)
		: WAL::System({}),
		  _window(window),
		  _camera(RAY::Vector2(10, 10), RAY::Vector2(), 0)
	{}

	void Render2DScreenSystem::onSelfUpdate()
	{
		this->_window.useCamera(this->_camera);
	}
}