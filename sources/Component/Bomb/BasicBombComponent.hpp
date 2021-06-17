//
// Created by Utilisateur on 08/06/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace BBM
{
	class BasicBombComponent : public WAL::Component
	{
	public:
		//! @brief The radius of the explosion.
		const int explosionRadius = 3;
		//! @brief The damage made by the explosion on an entity
		const int damage = 1;
		//! @brief The list of IDs of ignored entities.
		std::vector<unsigned> ignoredEntities;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief A component can't be instantiated, it should be derived.
		explicit BasicBombComponent(WAL::Entity &entity, int damage, int explosionRadius, std::vector<unsigned> ignored);

		//! @brief A component can't be instantiated, it should be derived.
		BasicBombComponent(const BasicBombComponent &) = default;

		//! @brief default destructor
		~BasicBombComponent() override = default;

		//! @brief A component can't be assigned
		BasicBombComponent &operator=(const BasicBombComponent &) = delete;
	};
}