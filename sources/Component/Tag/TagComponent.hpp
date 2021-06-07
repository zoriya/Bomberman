//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	class TagComponent : public WAL::Component
	{
		public:
			//! @brief tag held by the component
			std::string tag;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief Create a new tag Component with a tag
			explicit TagComponent(WAL::Entity &entity, std::string tag);

			//! @brief A Tag component is copy constructable.
			TagComponent(const TagComponent &) = default;

			//! @brief default destructor
			~TagComponent() override = default;

			//! @brief A Tag component can't be assigned
			TagComponent &operator=(const TagComponent &) = delete;
	};
}