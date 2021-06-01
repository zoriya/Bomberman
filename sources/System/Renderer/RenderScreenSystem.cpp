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
	{}

	void RenderScreenSystem::onSelfUpdate()
	{
		this->_window.draw();
		this->_window.clear();
		this->_window.useCamera(this->_camera);
	}

	void RenderScreenSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime)
	{
		const auto &pos = entity.getComponent<PositionComponent>();
		const auto &cam = entity.getComponent<CameraComponent>();
		_camera.setPosition(pos.position);
		_camera.setTarget(cam.target);
	}
}