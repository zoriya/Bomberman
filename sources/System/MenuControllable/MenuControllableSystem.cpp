//
// Created by Louis Auzuret 06/03/21
//

#include <algorithm>
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

	void MenuControllableSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &controllable = entity.getComponent<ControllableComponent>();
		auto buttons = ecs.view<<Button>(entities);
		std::sort(buttons.begin(), buttons.end(),
		[](WAL::Entity &first, WAL::Entity &second) {
			auto &posA = first.getComponent<PositionComponent>();
			auto &posB = second.getComponent<PositionComponent>();

			return (posA.position.y < posB.position.y);
		});
		_buttonIndex -= (controllable.move.y > 0);
		_buttonIndex += (controllable.move.y < 0);
		if (_buttonIndex < 0)
			_buttonIndex = buttons.length() - 1;
		_buttonIndex %= buttons.length();
		auto currentButton = buttons[_buttonIndex].getComponent<Button>();
		currentButton.onSelected();
		if (controllable.bomb)
			currentButton.onClick();
		std::for_each_n(buttons.begin(), _buttonIndex,
		[](WAL::Entity &curr) {
			curr.getComponent<Button>().onIdle();
		});
	}
}