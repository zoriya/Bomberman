/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ModelAnimation
*/

#ifndef MODELANIMATION_HPP_
#define MODELANIMATION_HPP_

#include <raylib.h>
#include <memory>

namespace RAY {
	//! @brief A Holder for Model Animations
	class ModelAnimation {
		public:
			//! @brief A Model animation constructor
			//! @param animationPtr an animation pointer, returned by the nimation-loading function
			ModelAnimation(::ModelAnimation *animationPtr);

			//! @brief A default copy-constructor
			ModelAnimation(const ModelAnimation &) = default;

			//! @brief A model animation is assignable
			ModelAnimation &operator=(const ModelAnimation &) = default;

			//! @brief Returns the current frame the animation is at
			size_t getFrameCounter() const;

			//! @brief Returns the number of frame in the animation
			size_t getFrameCount() const;

			//! @brief Set the frame the position is at
			ModelAnimation &setFrameCounter(size_t frameCounter);

			//! @brief Increment the frame counter
			ModelAnimation &incrementFrameCounter();

			//! @brief Default destructor
			~ModelAnimation() = default;

		private:
			::ModelAnimation *_animation;

			size_t _frameCounter;
		INTERNAL:
			//! @brief Castin Object to raw model animation pointer
			operator ::ModelAnimation *();

			//! @brief Castin Object to raw model animation pointer
			operator ::ModelAnimation() const;
	};
}


#endif /* !MODELANIMATION_HPP_ */
