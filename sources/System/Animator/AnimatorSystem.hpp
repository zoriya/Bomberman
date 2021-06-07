//
// Created by hbenjamin on 03/06/2021.
//

#pragma once

#include <Component/Renderer/Drawable3DComponent.hpp>
#include "Component/Animation/AnimationsComponent.hpp"
#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle Animator entities.
	class AnimatorSystem : public WAL::System<AnimationsComponent, ControllableComponent, Drawable3DComponent>
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<AnimationsComponent, ControllableComponent, Drawable3DComponent> &entity) override;

		//! @brief A default constructor
		AnimatorSystem(WAL::Wal &wal);
		//! @brief An Animator system is copy constructable
		AnimatorSystem(const AnimatorSystem &) = default;
		//! @brief A default destructor
		~AnimatorSystem() override = default;
		//! @brief An Animator system is assignable.
		AnimatorSystem &operator=(const AnimatorSystem &) = default;
	};
}