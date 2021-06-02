//
// Created by Zoe Roux on 5/27/21.
//

#undef INTERNAL
#define INTERNAL public
#include <Component/Renderer/Drawable2DComponent.hpp>
#include "RenderSystem.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Position/PositionComponent.hpp"

namespace BBM
{
	RenderSystem::RenderSystem(WAL::Wal &wal, RAY::Window &window)
		: WAL::System({
			typeid(CameraComponent),
			typeid(PositionComponent)
		}),
		_wal(wal),
		_window(window),
		_camera(Vector3f(), Vector3f(), Vector3f(0, 1, 0), 50, CAMERA_PERSPECTIVE)
	{}

	void RenderSystem::onSelfUpdate()
	{
		this->_camera.update();
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(this->_camera);
		for (auto &entity : this->_wal.scene->getEntities()) {
			if (!entity.hasComponent<Drawable2DComponent>()
		    || !entity.hasComponent<PositionComponent>())
				continue;
			auto &drawable = entity.getComponent<Drawable2DComponent>();
			auto &pos = entity.getComponent<PositionComponent>();

//			drawable.drawable->setPosition(static_cast<RAY::Vector3>(pos.position));
//			drawable.drawable->drawOn(this->_window);
		}
		EndMode3D();
		EndDrawing();
	}

	void RenderSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime)
	{
		const auto &pos = entity.getComponent<PositionComponent>();
		_camera.setPosition(pos.position);
	}
}