//
// Created by Zoe Roux on 5/27/21.
//

#include <Component/Renderer/Drawable3DComponent.hpp>
#include "Models/Vector2.hpp"
#include "RenderSystem.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include <Model/Model.hpp>
#include "Drawables/ADrawable3D.hpp"
#include "Component/Shaders/ShaderComponent.hpp"
#include <Drawables/3D/Cube.hpp>
#include "Models/Vector3.hpp"
#include "Component/Collision/CollisionComponent.hpp"

namespace BBM
{
	RenderSystem::RenderSystem(WAL::Wal &wal, RAY::Window &window, bool debugMode)
		: System(wal),
		  _window(window),
		  _camera(Vector3f(), Vector3f(), Vector3f(0, 1, 0), 50, CAMERA_PERSPECTIVE),
		  _debugMode(debugMode)
	{
		this->_window.setFPS(this->FPS);
	}

	void RenderSystem::drawBoundingBox(const WAL::Entity &entity, const PositionComponent &posComponent, const Drawable3DComponent &drawable) const
	{
		auto *dimsComponent = entity.tryGetComponent<CollisionComponent>();

		//draws hitbox
		if (dimsComponent) {
			RAY::Drawables::Drawables3D::Cube boundingBox(posComponent.position, dimsComponent->bound, WHITE);
			boundingBox.setDebugColor(RED);
			boundingBox.drawWiresOn(this->_window);
		}
		//draws models contours
		drawable.drawable->drawWiresOn(this->_window);
	}

	void RenderSystem::onSelfUpdate()
	{
		this->_camera.update();
		this->_window.beginDrawing();
		this->_window.clear();

		this->_window.useCamera(this->_camera);
		for (auto &[entity, pos, drawable] : this->_wal.getScene()->view<PositionComponent, Drawable3DComponent>()) {
			auto *modelShader = entity.tryGetComponent<ShaderComponentModel>();

			if (modelShader)
				modelShader->model->setShader(modelShader->getShader());
			drawable.drawable->setPosition(pos.position);
			drawable.drawable->drawOn(this->_window);
			if (modelShader)
				modelShader->model->resetShader();
			if (this->_debugMode)
				this->drawBoundingBox(entity, pos, drawable);
		}
		this->_window.unuseCamera();

		// TODO sort entities based on the Z axis
		for (auto &[entity, pos, drawable] : this->_wal.getScene()->view<PositionComponent, Drawable2DComponent>()) {
			auto *shader = entity.tryGetComponent<ShaderComponentDrawable2D>();

			if (shader) {
				RAY::Shader::BeginUsingCustomShader(shader->getShader());
			}
			drawable.drawable->setPosition(Vector2f(pos.position.x, pos.position.y));
			drawable.drawable->drawOn(this->_window);
			if (shader) {
				RAY::Shader::EndUsingCustomShader();
			}
		}
		if (this->_debugMode)
			this->_window.drawFPS(Vector2f(10, 10));
		this->_window.endDrawing();
	}

	void RenderSystem::onUpdate(WAL::ViewEntity<CameraComponent, PositionComponent> &entity,
	                            std::chrono::nanoseconds dtime)
	{
		const auto &pos = entity.get<PositionComponent>();
		const auto &cam = entity.get<CameraComponent>();
		_camera.setPosition(pos.position);
		_camera.setTarget(cam.target);
	}

	void RenderSystem::setDebug(bool debug)
	{
		this->_debugMode = debug;
	}
}