//
// Created by Louis Auzuret 06/03/21
//

#include <algorithm>
#include "Component/Button/ButtonComponent.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"
#include "Drawables/Texture.hpp"
#include "Drawables/2D/Text.hpp"
#include "Controllers/Mouse.hpp"

namespace RAYControl = RAY::Controller;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	MenuControllableSystem::MenuControllableSystem(WAL::Wal &wal)
		: System(wal),
		  _oldMousePosition(-1, -1),
		  currentButton()
	{
	}

	void MenuControllableSystem::_updateCurrentButton(bool selected, Vector2f move)
	{
		auto &buttonComponent = this->currentButton->getComponent<OnClickComponent>();
		WAL::Entity *newButton = nullptr; 

		if (move.y > 0 && buttonComponent._up)
			newButton = buttonComponent._up;
		if (move.y < 0 && buttonComponent._down)
			newButton = buttonComponent._down;
		if (move.x < 0 && buttonComponent._right)
			newButton = buttonComponent._right;
		if (move.x > 0 && buttonComponent._left)
			newButton = buttonComponent._left;

		if (newButton || selected) {
			auto lastTick = std::chrono::steady_clock::now();
			if (lastTick - this->now < std::chrono::milliseconds(150))
				return;
			this->now = lastTick;
		}

		if (newButton) {
			this->currentButton->getComponent<OnIdleComponent>().onEvent(*this->currentButton, this->_wal);
			this->currentButton = newButton;
			this->currentButton->getComponent<OnHoverComponent>().onEvent(*this->currentButton, this->_wal);
		}
		if (selected)
		    this->currentButton->getComponent<OnClickComponent>().onEvent(*this->currentButton, this->_wal);
	}

	bool MenuControllableSystem::_mouseOnButton(const Vector2f &mousePos, WAL::ViewEntity<OnClickComponent, OnHoverComponent, OnIdleComponent, PositionComponent, Drawable2DComponent> &entity) const
	{
		auto &positionComponent = entity.get<PositionComponent>();
		Vector2f buttonPos(positionComponent.getX(), positionComponent.getY());
		Vector2f dimensions;

		if (auto *texture = dynamic_cast<RAY::Texture *>(entity.get<Drawable2DComponent>().drawable.get())) {
			dimensions.x = texture->getDimensions().x;
			dimensions.y = texture->getDimensions().y;
		}
		else if (auto *text = dynamic_cast<RAY2D::Text *>(entity.get<Drawable2DComponent>().drawable.get())) {
			dimensions.y = text->getFontSize();
			dimensions.x = text->getString().size() * (text->getFontSize());
		}
		else
			return false;
		return ((buttonPos.x <= mousePos.x && mousePos.x <= buttonPos.x + dimensions.x)
			&& (buttonPos.y <= mousePos.y && mousePos.y <= buttonPos.y + dimensions.y));
	}

	void MenuControllableSystem::onSelfUpdate(std::chrono::nanoseconds)
	{
		RAY::Vector2 rayMousePos = RAYControl::Mouse::getCursorPosition();
		RAY::Vector2 winSize = RAY::Window::getInstance().getDimensions();
		Vector2f relativeMousePos(rayMousePos.x * 1920 / winSize.x, rayMousePos.y * 1080 / winSize.y);
		auto &controllableView = this->_wal.getScene()->view<ControllableComponent>();
		auto &buttons = _wal.getScene()->view<OnClickComponent, OnHoverComponent, OnIdleComponent, PositionComponent, Drawable2DComponent>();


		if (this->_oldMousePosition == Vector2f(-1, -1))
			this->_oldMousePosition = relativeMousePos;
		if (this->currentButton && this->currentButton->_scene.getID() != this->_wal.getScene()->getID()) {
			this->currentButton->getComponent<OnIdleComponent>().onEvent(*this->currentButton, this->_wal);
			this->currentButton = nullptr;
			return;
		}
		if (this->currentButton == nullptr && buttons.size()) {
			this->currentButton = &(*buttons.front());
			this->currentButton->getComponent<OnHoverComponent>().onEvent(*this->currentButton, this->_wal);
		}
		if (!this->currentButton)
			return;
		for (auto &[_, controllable]: controllableView)
			if (controllable.move.x || controllable.move.y || controllable.bomb) {
				this->_updateCurrentButton(controllable.bomb, controllable.move);
				return;
			}
		if (relativeMousePos == this->_oldMousePosition && !RAYControl::Mouse::isPressed(RAYControl::Mouse::Button::MOUSE_BUTTON_LEFT))
			return;
		this->_oldMousePosition = relativeMousePos;
		for (auto &entity:  buttons) {
			if (_mouseOnButton(relativeMousePos, entity)) {
				if (this->currentButton)
					this->currentButton->getComponent<OnIdleComponent>().onEvent(*this->currentButton, this->_wal);
				this->currentButton = &(*entity);
				this->currentButton->getComponent<OnHoverComponent>().onEvent(*this->currentButton, this->_wal);
				if (RAYControl::Mouse::isPressed(RAYControl::Mouse::Button::MOUSE_BUTTON_LEFT))
					this->currentButton->getComponent<OnClickComponent>().onEvent(*this->currentButton, this->_wal);
			}
		}
	}
}