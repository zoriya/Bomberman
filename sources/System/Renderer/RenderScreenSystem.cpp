//
// Created by Zoe Roux on 5/27/21.
//

#include "RenderScreenSystem.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Position/PositionComponent.hpp"

namespace BBM
{
	RenderScreenSystem::RenderScreenSystem(RAY::Window &window)
		: WAL::System({
			typeid(CameraComponent),
			typeid(PositionComponent)
		}),
		_window(window),
		_camera(Vector3f(), Vector3f(), Vector3f(0, 1, 0), 50, CAMERA_PERSPECTIVE)
	{
		this->_camera.setMode(CAMERA_FREE);
	}

	void RenderScreenSystem::onSelfUpdate()
	{
		//this->_window.draw();
		//EndMode2D();
		EndDrawing();
		this->_camera.update();
		BeginDrawing();
		this->_window.clear();
		BeginMode3D(this->_camera);
		printf("BeginMode3D\n");
	}

	void RenderScreenSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime)
	{
		const auto &pos = entity.getComponent<PositionComponent>();
		_camera.setPosition(pos.position);
		//this->_camera.update();
	}
}