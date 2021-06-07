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
		: System(wal), wal(wal)
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

	void MenuControllableSystem::onFixedUpdate(WAL::ViewEntity<ControllableComponent> &entity)
	{
		auto lastTick = std::chrono::steady_clock::now(); 
		
		if (lastTick - this->_now < std::chrono::milliseconds(100))
			return;
		this->_now = lastTick;
		auto &controllable = entity.get<ControllableComponent>();

		move = controllable.move;
		select = controllable.bomb;
		auto &buttons = wal.scene->view<OnClickComponent>();
		ssize_t index = 0;
		//std::sort(buttons.begin(), buttons.end(),
		//[](WAL::Entity &first, WAL::Entity &second) {
		//	auto &posA = first.getComponent<PositionComponent>();
		//	auto &posB = second.getComponent<PositionComponent>();
//
		//	return (posA.position.y < posB.position.y);
		//});
		updateButtonIndex(buttons.size());
		for (auto &button : buttons) {
			auto &buttonEntity = static_cast<WAL::Entity &>(button);
			if (index++ == _buttonIndex) {
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