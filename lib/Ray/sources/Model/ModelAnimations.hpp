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
#include "Utils/Cache.hpp"

namespace RAY {
	//! @brief A Holder for Model Animations
	class ModelAnimations {
		public:
			//! @brief A Model animation constructor
			//! @param filePath Path to the file containing animations
			ModelAnimations(const std::string &filePath);

			//! @brief default copy ctor
			ModelAnimations(const ModelAnimations &) = default;

			//! @brief Default constructor
			~ModelAnimations() = default;

			//! @brief Default assignment operator
			ModelAnimations &operator=(const ModelAnimations &) = default;

			//! @brief Castin Object to raw model animation pointer
			ModelAnimation &operator[](int index);

			//! @brief std [] const
			const ModelAnimation &operator[](int index) const;

			//! @brief std at const
			const ModelAnimation &at(int index) const;

			//! @brief std at
			ModelAnimation &at(int index);

			//! @return the number of loaded animations
			size_t getAnimationsCount() const;

			//! @brief Get the creation file
			std::string getFilePath() const;

		private:
			//! @brief Holds the pointer returned by the loading function
			std::shared_ptr<::ModelAnimation> _animationsPtr;

			//! @brief A holder for animations
			std::vector<ModelAnimation> _animations;

			//! @brief the number of loaded animations
			int _animationCount;

			//! @brief The file where the animations were loaded (used to create a copy of this class)
			const std::string _filePath;

			static Cache<::ModelAnimation> _animationsCache;
	};
}

#endif /* !MODELANIMATIONS_HPP_ */
