/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ModelAnimations
*/

#include "Model/ModelAnimations.hpp"

RAY::Cache<::ModelAnimation> RAY::ModelAnimations::_animationsCache(LoadModelAnimations, UnloadModelAnimations);

RAY::ModelAnimations::ModelAnimations(const std::string &filePath):
	_animationsPtr(_animationsCache.fetch(filePath, &this->_animationCount))
{
	::ModelAnimation *ptr = this->_animationsPtr.get();

	for (int i = 0; i < this->_animationCount; i++)
		this->_animations.emplace_back(RAY::ModelAnimation(ptr[i]));
}

RAY::ModelAnimation &RAY::ModelAnimations::operator[](int index)
{
	return this->_animations[index];
}

size_t RAY::ModelAnimations::getAnimationsCount() const
{
	return this->_animationCount;
}

