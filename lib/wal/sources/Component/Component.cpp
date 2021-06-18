//
// Created by Zoe Roux on 2021-05-14.
//

#include "Component/Component.hpp"

namespace WAL
{
	Component::Component(Entity &entity)
		: _entity(entity)
	{ }

	void Component::onStart()
	{
		// TODO handle events here
	}

	void Component::onStop()
	{
		// TODO handle events here
	}
} // namespace WAL