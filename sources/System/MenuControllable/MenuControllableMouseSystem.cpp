//
// Created by Louis Auzuret 06/03/21
//

#include <algorithm>
#include "Component/Button/ButtonComponent.hpp"
#include "System/MenuControllable/MenuControllableMouseSystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"
#include "Controllers/Mouse.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Drawables/Texture.hpp"
#include "Drawables/2D/Text.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"

namespace RAYControl = RAY::Controller;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	MenuControllableMouseSystem::MenuControllableMouseSystem(WAL::Wal &wal)
		: System(wal), _currentButton()
	{}

	void MenuControllableMouseSystem::onFixedUpdate(WAL::ViewEntity<ControllableComponent, PositionComponent, Drawable2DComponent> &entity)
	{
		auto &positionComponent = entity.get<PositionComponent>();
		RAY::Vector2 rayMousePos = RAYControl::Mouse::getCursorPosition();
		Vector2f buttonPos(positionComponent.getX(), positionComponent.getY());
		Vector2f mousePos(rayMousePos.x, rayMousePos.y);
		Vector2f dimensions;
		auto &controllable = entity.get<ControllableComponent>();

		if (this->_currentButton && this->_currentButton->_scene.getID() != this->_wal.getScene()->getID()) {
			this->_currentButton->getComponent<OnIdleComponent>().onEvent(*this->_currentButton, this->_wal);
			this->_currentButton = nullptr;
		}
		RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.get<Drawable2DComponent>().drawable.get());
		RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(entity.get<Drawable2DComponent>().drawable.get());
		WAL::Entity *newButton = nullptr; 

		if (texture) {
			dimensions.x = texture->getDimensions().x;
			dimensions.y = texture->getDimensions().y;
		} else if (text) {
			dimensions.y = text->getFontSize();
			dimensions.x = text->getString().size() * (text->getLetterSpacing() + text->getFontSize());
		} else
			return;
		if ((buttonPos.x <= mousePos.x && mousePos.x <= buttonPos.x + dimensions.x)
		&& (buttonPos.y <= mousePos.y && mousePos.y <= buttonPos.y + dimensions.y))
			newButton = &(*entity);
		if (newButton) {
			this->_currentButton->getComponent<OnIdleComponent>().onEvent(*this->_currentButton, this->_wal);
			this->_currentButton = newButton;
			this->_currentButton->getComponent<OnHoverComponent>().onEvent(*this->_currentButton, this->_wal);
			if (RAYControl::Mouse::isPressed(RAYControl::Mouse::Button::MOUSE_BUTTON_LEFT))
				this->_currentButton->getComponent<OnClickComponent>().onEvent(*this->_currentButton, this->_wal);
		}
	}
}