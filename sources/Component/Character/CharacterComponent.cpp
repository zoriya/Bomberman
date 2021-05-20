//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#include "CharacterComponent.hpp"

CharacterComponent::CharacterComponent(WAL::Entity &entity, BombComponent::BombType bombType)
: WAL::Component(entity)
{
    this->_bombType = bombType;
    this->_canTriggerRemote = false;
    this->_healthPoint = 1;
    this->_isHuman = false;
    this->_maxBombCount = 1;
    this->_playerNumber = ++this->_nextPlayer;
}

CharacterComponent::~CharacterComponent()
{

}

unsigned CharacterComponent::getPlayerNumber() const
{
    return (this->_playerNumber);
}

unsigned CharacterComponent::getHealthPoint() const
{
    return (this->_healthPoint);
}

unsigned CharacterComponent::getMaxBombCount() const
{
    return(this->_maxBombCount);
}

BombComponent::BombType CharacterComponent::getBombType() const
{
    return (this->_bombType);
}

bool CharacterComponent::isHuman() const
{
    return (this->_isHuman);
}

bool CharacterComponent::canTriggerRemote() const
{
    return (this->_canTriggerRemote);
}

void CharacterComponent::setPlayerNumber(unsigned playerNumber)
{
    this->_playerNumber = playerNumber;
}

void CharacterComponent::setHealthPoint(unsigned healthPoint)
{
    this->_healthPoint = healthPoint;
}

unsigned CharacterComponent::setMaxBombCount(unsigned maxBombCount)
{
    this->_maxBombCount = maxBombCount;
}

BombComponent::BombType CharacterComponent::setBombType(BombComponent::BombType bombType)
{
    this->_bombType = bombType;
}

bool CharacterComponent::setIsHuman(bool isHuman)
{
    this->_isHuman = isHuman;
}

bool CharacterComponent::setCanTriggerRemote(bool canTriggerRemote)
{
    this->_canTriggerRemote = canTriggerRemote;
}
