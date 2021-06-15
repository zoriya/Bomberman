//
// Created by hbenjamin on 09/06/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace BBM
{
	class PlayerBonusComponent : public WAL::Component
	{
	public:

		//! @brief The number of seconds before a speed bonus expire. This variable is used to reset the nextSpeedBonusRate value.
		std::chrono::nanoseconds speedBonusRate = 15s;
		//! @brief The number of nanosecond before the expiration of a speed bonus.
		std::chrono::nanoseconds nextSpeedBonusRate = speedBonusRate;
		//! @brief The number of seconds before a range bonus expire. This variable is used to reset the nextNoClipBonusRate value.
		std::chrono::nanoseconds noClipBonusRate = 5s;
		//! @brief The number of nanosecond before the expiration of a no clip bonus
		std::chrono::nanoseconds nextNoClipRate = noClipBonusRate;
		//! @brief To know if the player can clip through block
		bool isNoClipOn = false;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief A Bonus component can't be instantiated, it should be derived.
		explicit PlayerBonusComponent(WAL::Entity &entity);

		//! @brief A Bonus component can't be instantiated, it should be derived.
		PlayerBonusComponent(const PlayerBonusComponent &) = default;

		//! @brief default destructor
		~PlayerBonusComponent() override = default;

		//! @brief A Bonus component can't be assigned
		PlayerBonusComponent &operator=(const PlayerBonusComponent &) = delete;
	};
}