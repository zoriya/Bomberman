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
		: System(wal), wal(wal), currentButton()
	{}

	void MenuControllableSystem::updateCurrentButton(bool selected)
	{
		auto buttonComponent = this->currentButton->getComponent<OnClickComponent>();
		WAL::Entity *newButton = nullptr; 

		if (move.y > 0 && buttonComponent._up)
			newButton = buttonComponent._up;
		if (move.y < 0 && buttonComponent._down)
			newButton = buttonComponent._down;
		if (move.x < 0 && buttonComponent._right)
			newButton = buttonComponent._right;
		if (move.x > 0 && buttonComponent._left)
			newButton = buttonComponent._left;
		if (newButton) {
			this->currentButton->getComponent<OnIdleComponent>().onEvent(*this->currentButton, wal);
			this->currentButton = newButton;
			this->currentButton->getComponent<OnHoverComponent>().onEvent(*this->currentButton, wal);
		}
		if (selected)
		    this->currentButton->getComponent<OnClickComponent>().onEvent(*this->currentButton, wal);
	}

	void MenuControllableSystem::onFixedUpdate(WAL::ViewEntity<ControllableComponent> &entity)
	{
		auto lastTick = std::chrono::steady_clock::now(); 
		auto &controllable = entity.get<ControllableComponent>();
		auto &buttons = _wal.getScene()->view<OnClickComponent, OnHoverComponent, OnIdleComponent>();
		
		if (lastTick - this->_now < std::chrono::milliseconds(100))
			return;
		this->_now = lastTick;

		move = controllable.move;
		select = controllable.jump;
		if (currentButton && currentButton->_scene.getID() != wal.getScene()->getID()) {
			currentButton->getComponent<OnIdleComponent>().onEvent(*this->currentButton, wal);
			currentButton = nullptr;
		}
		if (currentButton == nullptr && buttons.size()) {
			currentButton = &(**buttons.begin());
			currentButton->getComponent<OnHoverComponent>().onEvent(*this->currentButton, wal);
		}
		if (!currentButton)
			return;
		this->updateCurrentButton(select);
	}

	void MenuControllableSystem::onSelfUpdate(void)
	{

	}
}