//
// Created by Tom Augier on 05/06/2021
//

#include "PlayerSoundManagerSystem.hpp"
#include <map>

namespace BBM {

	PlayerSoundManagerSystem::PlayerSoundManagerSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void PlayerSoundManagerSystem::onFixedUpdate(WAL::ViewEntity<SoundComponent, ControllableComponent, HealthComponent> &entity)
	{
		const auto &controllable = entity.get<ControllableComponent>();
		auto &sound = entity.get<SoundComponent>();
		auto &health = entity.get<HealthComponent>();
		
		sound.setVolume(sound.volume);
		std::map<bool, SoundComponent::SoundIndex> soundIndex = {
			{controllable.bomb, SoundComponent::BOMB},
			{controllable.jump, SoundComponent::JUMP},
			{controllable.move.x != 0 || controllable.move.y != 0, SoundComponent::MOVE}
		};
		for (auto &a : soundIndex) {
			if (a.first) {
				sound.setIndex(a.second);
				sound.playSound();
			}
		}
	}
}