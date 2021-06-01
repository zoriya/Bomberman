//
// Created by Zoe Roux on 6/1/21.
//

#pragma once

#include <System/System.hpp>
#include <vector>
#include <functional>

namespace BBM
{
	class EventSystem : public WAL::System
	{
	private:
		//! @brief The list of events that occurred in the last update.
		std::vector<std::function<void (WAL::Entity &)>> _events;
	public:
		//! @brief Inform the system that a new event has occurred and it should run the given method on every entities.
		void dispatchEvent(const std::function<void (WAL::Entity &)>& event);

		//! @inherit
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime) override;
		//! @inherit
		void onSelfUpdate() override;

		//! @brief A default constructor
		EventSystem();
		//! @brief An event system is copy constructable.
		EventSystem(const EventSystem &) = default;
		//! @brief A default destructor
		~EventSystem() override = default;
		//! @brief An event system is not assignable.
		EventSystem &operator=(const EventSystem &) = delete;
	};
}
