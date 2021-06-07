//
// Created by Tom Augier on 05/06/2021
//

#include "PlayerSoundManagerSystem.hpp"

namespace BBM {

    void SoundManagerSystem::onFixedUpdate(WAL::Entity &entity)
    {
        if (!entity.hasComponent<ControllableComponent>())
			return;
        const auto &controllable = entity.getComponent<ControllableComponent>();
        auto &sound = entity.getComponent<SoundComponent>();
        auto &health = entity.getComponent<HealthComponent>();

        sound.setIndex(SoundComponent::BOMB);
        controllable.bomb ? sound.loadSound() : sound.unloadSound();
        sound.setIndex(SoundComponent::JUMP);
        controllable.jump ? sound.loadSound() : sound.unloadSound();
        sound.setIndex(SoundComponent::MOVE);
        (controllable.move.x != 0 || controllable.move.y != 0) ? sound.loadSound() : sound.unloadSound();
        sound.setIndex(SoundComponent::DEATH);
        health.getHealthPoint() == 0 ? sound.loadSound() : sound.unloadSound();
    }
}