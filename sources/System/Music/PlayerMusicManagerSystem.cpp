//
// Created by Tom Augier on 05/06/2021
//

#include "PlayerMusicManagerSystem.hpp"

namespace BBM {

    void MusicManagerSystem::onFixedUpdate(WAL::Entity &entity)
    {
        if (!entity.hasComponent<ControllableComponent>())
			return;
        const auto &controllable = entity.getComponent<ControllableComponent>();
        auto &music = entity.getComponent<MusicComponent>();
        auto &health = entity.getComponent<HealthComponent>();

        music.setIndex(MusicComponent::BOMB);
        controllable.bomb ? music.loadMusic() : music.unloadMusic();
        music.setIndex(MusicComponent::JUMP);
        controllable.jump ? music.loadMusic() : music.unloadMusic();
        music.setIndex(MusicComponent::MOVE);
        (controllable.move.x != 0 || controllable.move.y != 0) ? music.loadMusic() : music.unloadMusic();
        music.setIndex(MusicComponent::DEATH);
        health.getHealthPoint() == 0 ? music.loadMusic() : music.unloadMusic();
    }
}