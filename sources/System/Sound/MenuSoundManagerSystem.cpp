//
// Created by Tom Augier on 05/06/2021
//

#include "MenuSoundManagerSystem.hpp"
#include <map>

namespace BBM {

	MenuSoundManagerSystem::MenuSoundManagerSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void MenuSoundManagerSystem::onFixedUpdate(WAL::ViewEntity<SoundComponent, ControllableComponent> &entity)
	{
		const auto &controllable = entity.get<ControllableComponent>();
		auto &sound = entity.get<SoundComponent>();
		
		sound.setVolume(sound.volume);
		std::map<bool, SoundComponent::SoundIndex> soundIndex = {
			{controllable.move.x, SoundComponent::MOVE},
			{controllable.move.y, SoundComponent::MOVE},
			{controllable.bomb,   SoundComponent::BOMB},
		};
		for (auto &a : soundIndex) {
			if (a.first) {
				sound.setIndex(a.second);
				sound.playSound();
			}
		}
	}
}