//
// Created by Louis Auzuret on 2021-05-24
//

#pragma once

#include "Controllers/Mouse.hpp"
#include "sources/Component/Clickable/ClickableComponent.hpp"
#include "sources/System/Clickable/ClickableSystem.hpp"

namespace BBM
{
	ClickableSystem::ClickableSystem()
	: WAL::System({typeid(ClickableComponent)})
	{ }
	void ClickableSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &clickable = entity.getComponent<ClickableComponent>();
		RAY::Controller::Mouse mouse;
		auto pos = mouse.getCursorPosition();
		if (pos.x && pos.y)
			clickable._onClick(entity);
	}
} //namespace BBM