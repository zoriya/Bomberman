//
// Created by Tom Augier on 5/26/21.
// Edited by Benjamin Henry on 5/26/21.
//

#pragma once

#include "Models/Vector3.hpp"
#include "Entity/Entity.hpp"
#include "Models/Callback.hpp"

namespace BBM
{
	//! @brief A component to place on entities that can collide.
	class ColliderComponent : public WAL::Component
	{
	public:

		WAL::Callback<const WAL::Entity &, WAL::Entity &> onCollide;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief Create a new movable component.
		explicit ColliderComponent(WAL::Entity &entity);

		//! @brief Create a new movable component with a callback.
		ColliderComponent::ColliderComponent(WAL::Entity &entity, std::function<void (const WAL::Entity &, WAL::Entity &)> callback);
		//! @brief A movable component is copy constructable.
		ColliderComponent(const ColliderComponent &) = default;
		//! @brief A default destructor
		~ColliderComponent() override = default;
		//! @brief A movable component is not assignable.
		ColliderComponent &operator=(const ColliderComponent &) = delete;

		friend class MovableSystem;
	};
} // namespace WAL