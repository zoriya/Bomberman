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

	void MenuControllableSystem::updateCurrentButton()
	{
		auto buttonComponent = this->currentButton->getComponent<OnClickComponent>();
		if (move.y > 0 && buttonComponent._up)
			this->currentButton = buttonComponent._up;
		if (move.y < 0 && buttonComponent._down)
			this->currentButton = buttonComponent._down;
		if (move.x > 0 && buttonComponent._right)
			this->currentButton = buttonComponent._right;
		if (move.x < 0 && buttonComponent._left)
			this->currentButton = buttonComponent._left;
		
	}

	void MenuControllableSystem::onFixedUpdate(WAL::ViewEntity<ControllableComponent> &entity)
	{
		auto lastTick = std::chrono::steady_clock::now(); 
		
		if (lastTick - this->_now < std::chrono::milliseconds(100))
			return;
		this->_now = lastTick;
		auto &controllable = entity.get<ControllableComponent>();

		move = controllable.move;
		select = controllable.bomb;
		auto &buttons = _wal.scene->view<OnClickComponent>();
		if (currentButton == nullptr && buttons.size()) {
			currentButton = &static_cast<WAL::Entity &>(buttons.front());
			std::cout << currentButton->getName() << std::endl;
			std::cout << currentButton->getUid() << std::endl;
			printf("%p\n", currentButton);
		}
		this->updateCurrentButton();
		for (auto &button : buttons) {
			auto &buttonEntity = static_cast<WAL::Entity &>(button);
			if (buttonEntity == *currentButton) {
				buttonEntity.getComponent<OnHoverComponent>().onEvent(button);
				if (select)
					button.get<OnClickComponent>().onEvent(button);
				continue;
			}
			buttonEntity.getComponent<OnIdleComponent>().onEvent(button);
		}
	}

	void MenuControllableSystem::onSelfUpdate(void)
	{

	}
}