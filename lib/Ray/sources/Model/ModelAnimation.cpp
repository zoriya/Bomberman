/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ModelAnimation
*/

#include <iostream>
#include "Model/ModelAnimation.hpp"

RAY::ModelAnimation::ModelAnimation(::ModelAnimation *animation):
	_animation(animation), _frameCounter(0)
{
}

size_t RAY::ModelAnimation::getFrameCounter() const
{
	return this->_frameCounter;
}

size_t RAY::ModelAnimation::getFrameCount() const
{
	return this->_animation->frameCount;
}

RAY::ModelAnimation &RAY::ModelAnimation::setFrameCounter(size_t frameCounter)
{
	std::cout << this << std::endl;
	std::cout << this->_animation << std::endl;
	std::cout << this->_animation->frameCount << std::endl;
	this->_frameCounter = frameCounter % this->_animation->frameCount;
	return *this;
}

RAY::ModelAnimation &RAY::ModelAnimation::incrementFrameCounter()
{
	this->_frameCounter = (this->_frameCounter + 1) % this->_animation->frameCount;
	return *this;
}


RAY::ModelAnimation::operator ::ModelAnimation() const
{
	return *this->_animation;
}

RAY::ModelAnimation::operator ::ModelAnimation *()
{
	return this->_animation;
}