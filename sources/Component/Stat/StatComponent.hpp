//
//
//

#pragma once

#include "Component/Component.hpp"
#include "Models/Callback.hpp"
#include "Wal.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"

namespace BBM
{
	//! @brief A Stat component which contains a text and a callback
	class StatComponent : public WAL::Component
	{
	public:
		//! @brief onEvent callback
		WAL::Callback<Drawable2DComponent &> updater;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief Create a new StatComponent with a callback
		StatComponent(WAL::Entity &entity, WAL::Callback<Drawable2DComponent &> callback);
		//! @brief A color component is copy constructable
		StatComponent(const StatComponent &) = default;
		//! @brief A default destructor
		~StatComponent() override = default;
		//! @brief A color component is not assignable
		StatComponent &operator=(const StatComponent &) = delete;
	};
} // namespace WAL