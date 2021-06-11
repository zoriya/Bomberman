//
// Created by Louis Auzuret 06/03/21
//

#include <algorithm>
#include "Component/Button/ButtonComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	MenuControllableSystem::MenuControllableSystem(WAL::Wal &wal)
		: System(wal),
		_currentButton()
	{}

	void MenuControllableSystem::_updateCurrentButton(bool selected, Vector2f move)
	{
		auto &buttonComponent = this->_currentButton->getComponent<OnClickComponent>();
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
			if (lastTick - this->_now < std::chrono::milliseconds(150))
				return;
			this->_now = lastTick;
		}

		if (newButton) {
			this->_currentButton->getComponent<OnIdleComponent>().onEvent(*this->_currentButton, this->_wal);
			this->_currentButton = newButton;
			this->_currentButton->getComponent<OnHoverComponent>().onEvent(*this->_currentButton, this->_wal);
		}
		if (selected)
		    this->_currentButton->getComponent<OnClickComponent>().onEvent(*this->_currentButton, this->_wal);
	}

	void MenuControllableSystem::onFixedUpdate(WAL::ViewEntity<ControllableComponent> &entity)
	{
		auto &controllable = entity.get<ControllableComponent>();
		auto &buttons = _wal.getScene()->view<OnClickComponent, OnHoverComponent, OnIdleComponent>();

		if (this->_currentButton && this->_currentButton->_scene.getID() != this->_wal.getScene()->getID()) {
			this->_currentButton->getComponent<OnIdleComponent>().onEvent(*this->_currentButton, this->_wal);
			this->_currentButton = nullptr;
		}
		if (this->_currentButton == nullptr && buttons.size()) {
			this->_currentButton = &(*buttons.front());
			this->_currentButton->getComponent<OnHoverComponent>().onEvent(*this->_currentButton, this->_wal);
		}
		if (!this->_currentButton)
			return;
		this->_updateCurrentButton(controllable.jump, controllable.move);
	}
}