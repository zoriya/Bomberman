//
// Created by cbihan on 01/06/2021.
//

#pragma once

#include <string>
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include "Model/Model.hpp"

namespace BBM
{

	class AnimationComponent : public WAL::Component
	{
	private:
		//! @brief To get the animation data
		RAY::ModelAnimation &_modelAnimation;
	public:
		//! @brief ctor entity and the path of the animation file
		explicit AnimationComponent(WAL::Entity &entity, RAY::ModelAnimation &modelAnimation);
		//! @brief copy ctor
		AnimationComponent(const AnimationComponent &) = default;
		//! @brief dtor
		~AnimationComponent() override = default;
		//! @brief assignment operator
		AnimationComponent &operator=(const AnimationComponent &) = delete;
	};

}
