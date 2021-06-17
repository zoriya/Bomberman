//
//
//

#pragma once

#include "Color.hpp"
#include "Component/Component.hpp"

namespace BBM
{
	//! @brief A basic color component
	class ColorComponent : public WAL::Component
	{
	public:
		//! @brief Get the editable color of this entity
		RAY::Color color;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief Create a new ColorComponent at a certain color
		ColorComponent(WAL::Entity &entity, RAY::Color color);
		//! @brief Create a new ColorComponent at a certain color
		ColorComponent(WAL::Entity &entity, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		//! @brief A color component is copy constructable
		ColorComponent(const ColorComponent &) = default;
		//! @brief A default destructor
		~ColorComponent() override = default;
		//! @brief A color component is not assignable
		ColorComponent &operator=(const ColorComponent &) = delete;
	};
} // namespace WAL