//
// Created by Zoe Roux on 2021-05-14.
//

#include "Component/Component.hpp"

namespace WAL
{
	Component::Component(Entity &entity)
		: _entity(entity)
	{ }

	bool Component::isDisabled() const
	{
		return this->_disabled;
	}

	void Component::setDisable(bool disabled)
	{
		this->_disabled = disabled;
	}

	void Component::onStart()
	{
		// TODO handle events here
	}

	void Component::onStop()
	{
		// TODO handle events here
	}
}