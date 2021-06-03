//
// Created by Louis Auzuret on 06/03/21.
//

#include "ButtonComponent.hpp"

namespace BBM
{
	ButtonComponent::ButtonComponent(WAL::Entity &entity)
	: WAL::Component(entity), onIdle(), onHover(), onClick()
	{ }

	WAL::Component *ButtonComponent::clone(WAL::Entity &entity) const
	{
		return new ButtonComponent(entity, onIdle, onHover, onClick);
	}

	ButtonComponent::ButtonComponent(WAL::Entity &entity, WAL::Callback<> idleCallback,
	WAL::Callback<> hoverCallback, WAL::Callback<> clickCallback)
	:	WAL::Component(entity),
		onIdle(idleCallback),
		onHover(hoverCallback),
		onClick(clickCallback)
	{ }
}