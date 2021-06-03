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
	MenuControllableSystem::MenuControllableSystem()
		: WAL::System({
			typeid(ControllableComponent)
		})
	{}

	void MenuControllableSystem::updateButtonIndex(int length)
	{
		_buttonIndex -= (move.y > 0);
		_buttonIndex += (move.y < 0);
		if (_buttonIndex < 0)
			_buttonIndex = length - 1;
		if (_buttonIndex == length)
			_buttonIndex = 0;
		
	}

	void MenuControllableSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &controllable = entity.getComponent<ControllableComponent>();

		move = controllable.move;
		select = controllable.bomb;
	}

	void MenuControllableSystem::onSelfUpdate(void)
	{
		auto buttons = ecs.view<<ButtonComponent>(entities);
		ssize_t index = 0;
		std::sort(buttons.begin(), buttons.end(),
		[](WAL::Entity &first, WAL::Entity &second) {
			auto &posA = first.getComponent<PositionComponent>();
			auto &posB = second.getComponent<PositionComponent>();

			return (posA.position.y < posB.position.y);
		});
		updateButtonIndex(buttons.length);
		auto currentButton = buttons[_buttonIndex].getComponent<ButtonComponent>();
		currentButton.onSelected();
		if (select)
			currentButton.onClick();
		for (auto &button : buttons) {
			if (index++ == _buttonIndex)
				continue;
			button.onIdle();
		}
	}
}