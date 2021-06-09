//
// Created by Zoe Roux on 6/1/21.
//

#pragma once

#include <System/System.hpp>
#include <vector>
#include <functional>

namespace BBM
{
	class EventSystem : public WAL::System<>
	{
	private:
		//! @brief The list of events that occurred in the last update.
		std::list<std::function<void (WAL::Entity &)>> _events;
		//! @brief The list of events that occurred in the last update.
		std::list<std::function<void (WAL::Wal &)>> _globalEvents;
	public:
		//! @brief Inform the system that a new event has occurred and it should run the given method on every entities.
		void dispatchEvent(const std::function<void (WAL::Entity &)>& event);

		//! @brief Inform the system that a new event has occurred and it should run the given method on every entities.
		void dispatchEvent(const std::function<void (WAL::Wal &)>& event);

		//! @inherit
		void onUpdate(WAL::ViewEntity<> &entity, std::chrono::nanoseconds dtime) override;
		//! @inherit
		void onSelfUpdate() override;

		//! @brief A default constructor
		explicit EventSystem(WAL::Wal &wal);
		//! @brief An event system is copy constructable.
		EventSystem(const EventSystem &) = default;
		//! @brief A default destructor
		~EventSystem() override = default;
		//! @brief An event system is not assignable.
		EventSystem &operator=(const EventSystem &) = delete;
	};
}
