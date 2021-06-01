//
// Created by cbihan on 01/06/2021.
//

#pragma once

#include <string>
#include <Model/ModelAnimations.hpp>
#include <Component/Component.hpp>
#include <Entity/Entity.hpp>

namespace BBM
{
	class AnimationsComponent : public WAL::Component
	{
	private:
		//! @brief To get the animation data
		RAY::ModelAnimations &_modelAnimation;
		//! @brief the frame animation counter
		size_t _animFrameCounter;
	public:
		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief get animation frame counter
		size_t getAnimFrameCounter() const;

		//! @brief get the current
		RAY::ModelAnimation getCurrentModelAnim() const;

		//! @brief
		void setAnimFrameCounter(size_t animFrameCounter);

		//! @brief Set the internal anim counter to 0
		void resetAnimFrameCounter();

		//! @brief ctor entity and the path of the animation file
		explicit AnimationsComponent(WAL::Entity &entity, RAY::ModelAnimations &modelAnimation);
		//! @brief copy ctor
		AnimationsComponent(const AnimationsComponent &) = default;
		//! @brief dtor
		~AnimationsComponent() override = default;
		//! @brief assignment operator
		AnimationsComponent &operator=(const AnimationsComponent &) = delete;
	};

}
