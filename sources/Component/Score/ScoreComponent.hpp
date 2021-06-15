
#pragma once

#include "Component/Component.hpp"

namespace BBM
{
	//! @brief A basic position component
	class ScoreComponent : public WAL::Component
	{
	public:
        //! @brief score of player (4 is the looser, 1 is the winner)
        enum Score {FIRST = 1, SECOND = 2, THIRD = 3, FOURTH = 4, PLAYING = -1};
		//! @brief the score of the player
		enum Score position;

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