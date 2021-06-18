//
// Created by hbenjamin on 6/18/21.
//

#pragma once

#include <Component/Component.hpp>
#include <Entity/Entity.hpp>
#include <Color.hpp>
#include <Component/Controllable/ControllableComponent.hpp>
#include <chrono>

namespace BBM
{
	class ResumeLobbyComponent : public WAL::Component
	{
	public:
		//! @brief The layout used for this player.
		ControllableComponent::Layout layout = ControllableComponent::NONE;
		//! @brief The ID of the lobby player (from 0 to 3)
		int playerID;
		//! @brief The color of the player (as an index)
		int color;
		//! @brief Is this player ready
		bool ready = false;
		//! @brief The entity containing the ready display.
		WAL::Entity &readyButton;
		//! @brief The colored rectangle behind the player.
		WAL::Entity &coloredTile;
		//! @brief The time of last input that this lobby player has made.
		std::chrono::time_point<std::chrono::steady_clock> lastInput;

		Component *clone(WAL::Entity &entity) const override;

		//! @brief Create a new lobby component.
		explicit ResumeLobbyComponent(WAL::Entity &entity, int playerNumber, WAL::Entity &button, WAL::Entity &tile, int color);
		//! @brief A lobby component is copyable.
		ResumeLobbyComponent(const ResumeLobbyComponent &) = default;
		//! @brief A default destructor
		~ResumeLobbyComponent() override = default;
		//! @brief A lobby component is not assignable.
		ResumeLobbyComponent &operator=(const ResumeLobbyComponent &) = delete;
	};
}
