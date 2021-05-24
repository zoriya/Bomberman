/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ModelAnimations
*/

#include "Model/ModelAnimations.hpp"

RAY::ModelAnimations::ModelAnimations(const std::string &filePath):
	_animationsPtr(LoadModelAnimations(filePath.c_str(), &this->_animationCount))
{
	::ModelAnimation *ptr = this->_animationsPtr.get();
	for (int i = 0; i < this->_animationCount; i++)
		this->_animations.push_back(RAY::ModelAnimation(ptr[i]));
}

RAY::ModelAnimations::~ModelAnimations()
{
	UnloadModelAnimations(this->_animationsPtr.release(), this->_animationCount);
}

RAY::ModelAnimation &RAY::ModelAnimations::operator[](int index)
{
	return this->_animations[index];
}

size_t RAY::ModelAnimations::getAnimationsCount() const
{
	return this->_animationCount;
}

