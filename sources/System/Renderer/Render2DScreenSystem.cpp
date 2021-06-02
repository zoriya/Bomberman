//
// Created by Zoe Roux on 5/27/21.
//

#include "Render2DScreenSystem.hpp"

namespace BBM
{
	Render2DScreenSystem::Render2DScreenSystem(RAY::Window &window)
		: WAL::System({}),
		  _window(window)
	{}

	void Render2DScreenSystem::onSelfUpdate()
	{
		EndMode3D();
		printf("EndMode3D\n");
		DrawText("Try selecting the box with mouse!", 10, 10, 20, WHITE);
		//this->_window.unuseCamera();
	}
}