//
// Created by Tom Augier on 05/06/2021
//

#include "PlayerSoundManagerSystem.hpp"

namespace BBM {

    
	SoundManagerSystem::SoundManagerSystem()
		: WAL::System({
			typeid(SoundComponent),
            typeid(HealthComponent)
		})
	{}

    void SoundManagerSystem::onFixedUpdate(WAL::Entity &entity)
    {
        if (!entity.hasComponent<ControllableComponent>())
			return;
        const auto &controllable = entity.getComponent<ControllableComponent>();
        auto &sound = entity.getComponent<SoundComponent>();
        auto &health = entity.getComponent<HealthComponent>();

        sound.setIndex(SoundComponent::BOMB);
        if (controllable.bomb)
            sound.playSound();
        sound.setIndex(SoundComponent::JUMP);
        if (controllable.jump)
            sound.playSound();
        sound.setIndex(SoundComponent::MOVE);
        if (controllable.move.x != 0 || controllable.move.y != 0)
            sound.playSound();
    }
}