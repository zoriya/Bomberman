//
// Created by Zoe Roux on 5/24/21.
//

#pragma once

#include <Component/Component.hpp>

namespace BBM
{
	//! @brief A component to slowly center entities to the middle of their current block.
	//!        This allow flexibility in their movement will preventing them from getting stuck at every corner.
	class GridCenteredComponent : public WAL::Component
	{
	public:
		//! @brief The force factor applied at each frame.
		float force = 1;

		//! @inherit
		Component *clone(WAL::Entity &entity) const override;

		//! @brief Create a new, default GridCenteredComponent.
		//! @param entity The entity attached to this component.
		explicit GridCenteredComponent(WAL::Entity &entity);
		//! @brief A GridCenteredComponent is copy constructable
		//! @param other The other GridCenteredComponent to copy.
		GridCenteredComponent(const GridCenteredComponent &other) = default;
		//! @brief A default destructor
		~GridCenteredComponent() override = default;
		//! @brief A GridCenteredComponent is not assignable
		GridCenteredComponent &operator=(const GridCenteredComponent &) = delete;
	};
}
