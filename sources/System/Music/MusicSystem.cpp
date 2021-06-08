//
// Created by Tom Augier on 05/06/2021
//

#include "MusicSystem.hpp"
#include <map>

namespace BBM {

	MusicSystem::MusicSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void MusicSystem::onFixedUpdate(WAL::ViewEntity<MusicComponent> &entity)
	{
		auto &music = entity.get<MusicComponent>();
		
		music.setVolume(music.volume);
		if (!music.isPlaying())
			music.playMusic();
		music.updateMusicStream();
		
	}
}