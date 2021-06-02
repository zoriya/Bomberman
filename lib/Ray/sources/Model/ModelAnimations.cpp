/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ModelAnimations
*/

#include "Model/ModelAnimations.hpp"

RAY::Cache<::ModelAnimation> RAY::ModelAnimations::_animationsCache(LoadModelAnimations, UnloadModelAnimations);

RAY::ModelAnimations::ModelAnimations(const std::string &filePath):
	_animationsPtr(_animationsCache.fetch(filePath, &this->_animationCount)),
	_filePath(filePath)
{
	::ModelAnimation *ptr = this->_animationsPtr.get();

	for (int i = 0; i < this->_animationCount; i++)
		this->_animations.emplace_back(ptr[i]);
}

RAY::ModelAnimation &RAY::ModelAnimations::operator[](int index)
{
	return this->_animations[index];
}

size_t RAY::ModelAnimations::getAnimationsCount() const
{
	return this->_animationCount;
}

std::string RAY::ModelAnimations::getFilePath() const
{
	return this->_filePath;
}

const RAY::ModelAnimation &RAY::ModelAnimations::at(int index) const
{
	return this->_animations.at(index);
}

const RAY::ModelAnimation &RAY::ModelAnimations::operator[](int index) const
{
	return this->_animations[index];
}

RAY::ModelAnimation &RAY::ModelAnimations::at(int index)
{
	return this->_animations.at(index);
}
