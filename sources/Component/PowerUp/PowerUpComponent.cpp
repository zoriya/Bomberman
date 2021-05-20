//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#include "PowerUpComponent.hpp"

PowerUpComponent::PowerUpComponent(WAL::Entity &entity, PowerUpType powerType, int duration, bool infinite)
: WAL::Component(entity)
{
    this->_duration = duration;
    this->_isInfinite = infinite;
    this->_powerUpType = powerType;
}

PowerUpComponent::~PowerUpComponent()
{

}

bool PowerUpComponent::getIsInfinite() const
{
    return (this->_isInfinite);
}

unsigned PowerUpComponent::getDuration() const
{
    return (this->_duration);
}

PowerUpComponent::PowerUpType PowerUpComponent::getPowerUpType() const
{
    return (this->_powerUpType);
}

void PowerUpComponent::setIsInfinite(bool isInfinite)
{
    this->_isInfinite = isInfinite;
}

void PowerUpComponent::setDuration(unsigned duration)
{
    this->_duration = duration;
}

void PowerUpComponent::setPowerUpType(PowerUpType powerUpType)
{
    this->_powerUpType = powerUpType;
}