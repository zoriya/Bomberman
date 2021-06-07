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
		return new ButtonComponent(entity, onIdle, onHover, onClick, onHold);
	}

	ButtonComponent::ButtonComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &> idleCallback,
	WAL::Callback<WAL::Entity &> hoverCallback, WAL::Callback<WAL::Entity &> clickCallback, WAL::Callback<WAL::Entity &> holdCallback)
	:	WAL::Component(entity),
		onIdle(idleCallback),
		onHover(hoverCallback),
		onClick(clickCallback),
		onHold(holdCallback)
	{ }

	void ButtonComponent::emptyButtonCallback(WAL::Entity &)
	{ }
}