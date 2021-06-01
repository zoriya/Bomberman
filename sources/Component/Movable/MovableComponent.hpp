//
// Created by Zoe Roux on 5/17/21.
//

#pragma once

#include "Models/Vector3.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	//! @brief A component to place on entities that can move or be moved.
	class MovableComponent : public WAL::Component
	{
	private:
		//! @brief The acceleration of this entity.
		Vector3f _acceleration;
		//! @brief The velocity of the entity.
		Vector3f _velocity;
	public:

		//! @brief Add an instant force to this entity.
		//! @param force The force to add to this entity's acceleration. The force is added instantly and in one go.
		void addForce(Vector3f force);

		//! @brief Set velocity to 0
		void resetVelocity(void);

		//! @brief Get velocity
		const Vector3f &getVelocity(void) const;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief Create a new movable component.
		explicit MovableComponent(WAL::Entity &entity);
		//! @brief A movable component is copy constructable.
		MovableComponent(const MovableComponent &) = default;
		//! @brief A default destructor
		~MovableComponent() override = default;
		//! @brief A movable component is not assignable.
		MovableComponent &operator=(const MovableComponent &) = delete;

		friend class MovableSystem;
	};
} // namespace WAL