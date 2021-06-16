
#pragma once

#include "Component/Component.hpp"
#include <chrono>

namespace BBM
{
	//! @brief A basic position component
	class ScoreComponent : public WAL::Component
	{
	public:
		//! @brief the score of the player
		std::chrono::nanoseconds aliveTime;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief Create a new ScoreComponent linked to a specific entity
		explicit ScoreComponent(WAL::Entity &entity);
		//! @brief A position component is copy constructable
		ScoreComponent(const ScoreComponent &) = default;
		//! @brief A default destructor
		~ScoreComponent() override = default;
		//! @brief A position component is not assignable
		ScoreComponent &operator=(const ScoreComponent &) = delete;
	};
} // namespace WAL