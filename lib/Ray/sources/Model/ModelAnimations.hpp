/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ModelAnimations
*/

#ifndef MODELANIMATIONS_HPP_
#define MODELANIMATIONS_HPP_

#include "Model/ModelAnimation.hpp"
#include <vector>
#include <string>

namespace RAY {
	//! @brief A Holder for Model Animations
	class ModelAnimations {
		public:
			//! @brief A Model animation constructor
			//! @param filePath Path to the file containing animations
			ModelAnimations(const std::string &filePath);

			//! @brief Only single entity can hold these animations pointers
			ModelAnimations(const ModelAnimations &) = delete;

			//! @brief Unloads all animations
			~ModelAnimations();

			//! @brief Only single entity can hold these animations pointers
			ModelAnimations &operator=(const ModelAnimations &) = delete;

			//! @brief Castin Object to raw model animation pointer
			ModelAnimation &operator[](int index);

			//! @return the number of loaded animations
			size_t getAnimationsCount() const;

		private:
			//! @brief Holds the pointer returned by the loading function
			std::unique_ptr<::ModelAnimation> _animationsPtr;

			//! @brief A holder for animations
			std::vector<ModelAnimation> _animations;

			//! @brief the number of loaded animations
			int _animationCount;
	};
}

#endif /* !MODELANIMATIONS_HPP_ */
