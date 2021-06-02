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
		RAY::ModelAnimations _modelAnimation;
		//! @brief The index of the
		int _currentAnimIndex;
		//! @brief Bool allowing to play pause an animation
		bool _animDisabled;
	public:
		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief get the current animation index
		size_t getCurrentAnimIndex() const;

		//! @brief Set the animation index to use
		void setAnimIndex(int animIndex);

		//! @brief get animation frame counter
		size_t getCurrentAnimFrameCounter() const;

		//! @brief get the current
		RAY::ModelAnimation getCurrentModelAnim();

		//! @brief set the anim frame counter
		void setCurrentAnimFrameCounter(size_t animFrameCounter);

		//! @brief Set the internal anim counter to 0
		void resetCurrentAnimFrameCounter();

		//! @brief Increment the internal anim counter
		void incCurrentAnimFrameCounter();

		//! @brief Allow to play pause animations
		void setAnimDisabled(bool disable);

		//! @brief To know if the animation will be updated or not
		bool isAnimDisabled() const;

		//! @brief ctor entity and the path of the animation file
		explicit AnimationsComponent(WAL::Entity &entity, RAY::ModelAnimations modelAnimation, int animIndex, bool play = true);
		//! @brief copy ctor
		AnimationsComponent(const AnimationsComponent &) = default;
		//! @brief dtor
		~AnimationsComponent() override = default;
		//! @brief assignment operator
		AnimationsComponent &operator=(const AnimationsComponent &) = delete;
	};

}
