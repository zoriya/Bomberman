//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "MouseSystem.hpp"
#include "sources/Component/Mouse/MouseComponent.hpp"
#include "sources/Component/Clickable/ClickableComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	const std::type_info &MouseSystem::getComponent() const
	{
		return typeid(MouseComponent);
	}

	void MouseSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &mouse = entity.getComponent<MouseComponent>();
		auto &clickable = entity.getComponent<ClickableComponent>();
		static const std::map<int, bool> keyPressedMap = {
			{mouse.leftClick, clickable.jump},
			{mouse.rightClick, clickable.bomb},
			{mouse.middleClick, clickable.pause}
		};


	}
}