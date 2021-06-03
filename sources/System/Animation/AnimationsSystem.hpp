//
// Created by cbihan on 01/06/2021.
//

#pragma once

#include <System/System.hpp>
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Component/Animation/AnimationsComponent.hpp"

namespace BBM
{
	class AnimationsSystem : public WAL::System<Drawable3DComponent, AnimationsComponent>
	{
	public:
		//! @inherit
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds) override;

		//! @brief A default constructor
		explicit AnimationsSystem(WAL::Wal &wal);
		//! @brief A Controllable system is copy constructable
		AnimationsSystem(const AnimationsSystem &) = default;
		//! @brief A default destructor
		~AnimationsSystem() override = default;
		//! @brief A system is not assignable.
		AnimationsSystem &operator=(const AnimationsSystem &) = delete;
	};
}