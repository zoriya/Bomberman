//
// Created by Zoe Roux on 6/1/21.
//

#include "EventSystem.hpp"

namespace BBM
{
	EventSystem::EventSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void EventSystem::dispatchEvent(const std::function<void(WAL::Entity &)> &event)
	{
		this->_events.emplace_back(event);
	}

	void EventSystem::dispatchEvent(const std::function<void(WAL::Wal &)> &event)
	{
		this->_globalEvents.emplace_back(event);
	}

	void EventSystem::onUpdate(WAL::ViewEntity<> &entity, std::chrono::nanoseconds)
	{
		for (auto &event : this->_events)
			event(entity);
	}

	void EventSystem::onSelfUpdate()
	{
		for (auto &event : this->_globalEvents)
			event(this->_wal);
		this->_events.clear();
		this->_globalEvents.clear();
	}
}