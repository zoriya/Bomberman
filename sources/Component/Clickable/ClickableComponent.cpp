//
// Created by Louis Auzuret on 2021-05-24
//

#pragma once
#include "Clickable/ClickableComponent.hpp"

namespace BBM
{
    
    ClickableComponent::ClickableComponent(WAL::Entity &entity):
        Component(entity), _onClick()
    {
    }

    ClickableComponent *ClickableComponent::clone(WAL::Entity &entity) const
    {
        return new ClickableComponent(entity);
    }

    int ClickableComponent::addCallback(std::function<void (WAL::Entity &)> callback)
    {
        return _onClick.addCallback(callback);
    }
}