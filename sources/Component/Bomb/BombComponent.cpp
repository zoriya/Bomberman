//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#include "BombComponent.hpp"

BombComponent::BombComponent(WAL::Entity &entity, BombType bombType, unsigned int ownerUid)
: WAL::Component(entity)
{
    this->_bombType = bombType;
    this->_ownerUid = ownerUid;
    this->_isGhosting = bombType == BombComponent::DANGEROUS ? true : false;
    this->_isBreakingWall = false;
    this->_explosionDist = 0;
    this->_explosionHeight = 0;
    this->_countdown = 0;
    this->_explosionDamage = 0;
}

BombComponent::~BombComponent()
{

}

unsigned BombComponent::getCountdown() const
{
    return (this->_countdown);
}

unsigned BombComponent::getExplosionDist() const
{
    return (this->_explosionDist);
}

unsigned BombComponent::getExplosionHeight() const
{
    return (this->_explosionHeight);
}

unsigned BombComponent::getExplosionDamage() const
{
    return (this->_explosionDamage);
}

unsigned BombComponent::getOwnerUid() const
{
    return (this->_ownerUid);
}

bool BombComponent::isBreakingWall() const
{
    return (this->_isBreakingWall);
}

bool BombComponent::isGhosting() const
{
    return (this->_isGhosting);
}

void BombComponent::setCountdown(unsigned countdown)
{
    this->_countdown = countdown;
}

void BombComponent::setExplosionDist(unsigned explosionDist)
{
    this->_explosionDist = explosionDist;
}

void BombComponent::setExplosionHeight(unsigned explosionHeight)
{
    this->_explosionHeight = explosionHeight;
}

void BombComponent::setExplosionDamage(unsigned explosionDamage)
{
    this->_explosionDamage = explosionDamage;
}

void BombComponent::setOwnerUid(unsigned ownerUid)
{
    this->_ownerUid = ownerUid;
}

void BombComponent::setBreakingWall(bool isBreakingWall)
{
    this->_isBreakingWall = isBreakingWall;
}

void BombComponent::setGhosting(bool isGhosting)
{
    this->_isBreakingWall = isBreakingWall;
}
