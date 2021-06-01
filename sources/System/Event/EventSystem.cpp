//
// Created by Zoe Roux on 6/1/21.
//

#include "EventSystem.hpp"

namespace BBM
{
	EventSystem::EventSystem()
		: WAL::System({})
	{}

	void EventSystem::dispatchEvent(const std::function<void(WAL::Entity &)> &event)
	{
		this->_events.emplace_back(event);
	}

	void EventSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds)
	{
		for (auto &event : this->_events)
			event(entity);
	}

	void EventSystem::onSelfUpdate()
	{
		this->_events.clear();
	}
}