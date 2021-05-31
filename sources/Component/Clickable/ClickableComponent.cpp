//
// Created by Louis Auzuret on 2021-05-24
//

#pragma once
#include "Clickable/ClickableComponent.hpp"

namespace BBM
{
    
    ClickableComponent::ClickableComponent(WAL::Entity &entity):
        Component(entity), _callbacks(3)
    {

    }

    ClickableComponent *ClickableComponent::clone(WAL::Entity &entity) const
    {
        return new ClickableComponent(entity);
    }

    int ClickableComponent::addCallback(ClickableComponent::CallbackType type, std::function<void (WAL::Entity &)> callback)
    {
        return this->_callbacks[type].addCallback(callback);
    }

    int ClickableComponent::addClickCallback(std::function<void (WAL::Entity &)> callback)
    {
        return this->_callbacks[CLICK].addCallback(callback);
    }

    int ClickableComponent::addHoverCallback(std::function<void (WAL::Entity &)> callback)
    {
        return this->_callbacks[HOVER].addCallback(callback);
    }

    int ClickableComponent::addIdleCallback(std::function<void (WAL::Entity &)> callback)
    {
        return this->_callbacks[IDLE].addCallback(callback);
    }
}