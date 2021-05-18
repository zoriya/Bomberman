//
// Created by Zoe Roux on 5/17/21.
//

#pragma once

#include "Models/Vector3.hpp"
#include "Component/Component.hpp"

namespace WAL
{
	//! @brief A basic position component
	class PositionComponent : public Component
	{
	public:
		//! @brief Get the editable position of this entity
		Vector3f position;

		//! @brief Get the X position of this entity.
		float getX() const;
		//! @brief Get the Y position of this entity.
		float getY() const;
		//! @brief Get the Z position of this entity.
		float getZ() const;

		//! @inherit
		Component *clone(Entity &entity) const override;

		//! @brief Create a new PositionComponent linked to a specific entity
		explicit PositionComponent(Entity &entity);
		//! @brief Create a new PositionComponent at a certain position
		PositionComponent(Entity &entity, Vector3f pos);
		//! @brief Create a new PositionComponent at a certain position
		PositionComponent(Entity &entity, float x, float y, float z);
		//! @brief A position component is copy constructable
		PositionComponent(const PositionComponent &) = default;
		//! @brief A default destructor
		~PositionComponent() override = default;
		//! @brief A position component is not assignable
		PositionComponent &operator=(const PositionComponent &) = delete;
	};
}
