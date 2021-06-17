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
#include "Drawables/ADrawable2D.hpp"
#include "Component/Shaders/ShaderComponent.hpp"
#include <Drawables/3D/Cube.hpp>
#include "Models/Vector3.hpp"
#include "Component/Collision/CollisionComponent.hpp"
#include <Drawables/2D/Text.hpp>
#include <Drawables/2D/Rectangle.hpp>

namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	RenderSystem::RenderSystem(WAL::Wal &wal, RAY::Window &window, bool debugMode)
		: System(wal),
		  _window(window),
		  _camera(Vector3f(), Vector3f(), Vector3f(0, 1, 0), 50, CAMERA_PERSPECTIVE),
		  _debugMode(debugMode)
	{
		this->_window.setFPS(BBM::RenderSystem::FPS);
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

	Vector2f RenderSystem::getRescaledPosition(Vector3f &position, const Vector2f &newWinDims)
	{
		Vector2f newPosition;
		newPosition.x = (position.x * newWinDims.x) / 1920;
		newPosition.y = (position.y * newWinDims.y) / 1080;
		return newPosition;
	}

	void RenderSystem::drawRescaledDrawable(RAY::Drawables::ADrawable2D &drawable, const Vector2f &newDims)
	{
		RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(&drawable);

		if (text) {
			float oldHeightSize = text->getFontSize();
			float oldWidthSize = text->getFontSize() + text->getLetterSpacing();
			float newHeightSize = oldHeightSize * newDims.y / 1080;
			float newWidthSize = oldWidthSize * newDims.x / 1920;
			text->setFontSize((newWidthSize + newHeightSize) / 2);
			drawable.drawOn(this->_window);
			text->setFontSize(oldHeightSize);
			return;
		}
		RAY::Texture *texture = dynamic_cast<RAY::Texture *>(&drawable);

		if (texture) {
			float oldScale = texture->getScale();
			float newScale = (texture->getWidth() * newDims.x / 1920) / texture->getWidth();
			texture->setScale(newScale);
			drawable.drawOn(this->_window);
			texture->setScale(oldScale);
			return;
		}
		RAY2D::Rectangle *rect = dynamic_cast<RAY2D::Rectangle *>(&drawable);

		if (rect) {
			float oldHeightSize = rect->getHeight();
			float oldWidthSize = rect->getWidth();
			rect->setHeight(oldHeightSize * newDims.y / 1080);
			rect->setWidth(oldWidthSize * newDims.x / 1920);
			drawable.drawOn(this->_window);
			rect->setWidth(oldWidthSize);
			rect->setHeight(oldHeightSize);
			return;
		}
	}

	void RenderSystem::resizeWindow(Vector2f &newDims)
	{
		newDims.y = (newDims.x * 720) / 1280;
		if ((newDims.y < 720 || newDims.x < 1280))  {
			newDims.y = 720;
			newDims.x = 1280;
		}
		this->_window.setDimensions(newDims);
	}

	void RenderSystem::onSelfUpdate(std::chrono::nanoseconds dtime)
	{
		this->_camera.update();
		this->_window.beginDrawing();
		this->_window.clear();
		RAY::Vector2 rayWinDims = this->_window.getDimensions();
		Vector2f windowDimensions(rayWinDims.x, rayWinDims.y);

		this->resizeWindow(windowDimensions);

		for (auto &[entity, pos, drawable] : this->_wal.getScene()->view<PositionComponent, Drawable2DComponent>()) {
			if (!drawable.drawBefore3D)
				continue;
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
			if (drawable.drawBefore3D)
				continue;
			auto *shader = entity.tryGetComponent<ShaderComponentDrawable2D>();

			if (shader) {
				RAY::Shader::BeginUsingCustomShader(shader->getShader());
			}
			drawable.drawable->setPosition(this->getRescaledPosition(pos.position, windowDimensions));
			this->drawRescaledDrawable(*drawable.drawable, windowDimensions);
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