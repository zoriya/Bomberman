//
// Created by Louis Auzuret on 2021-05-24
//

#pragma once

#include "Component/Clickable/ClickableComponent.hpp"
#include "System/Clickable/ClickableSystem.hpp"

namespace BBM
{
	ClickableSystem::ClickableSystem()
	: WAL::System({typeid(ClickableComponent)})
	{ }
	void ClickableSystem::onFixedUpdate(WAL::Entity &entity)
	{
		//get Mouse ray, if collide with renderer box, call callback of the component
	}
} //namespace BBM