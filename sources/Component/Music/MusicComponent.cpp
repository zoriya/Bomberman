//
// Created by Tom Augier on 05/06/2021
//

#include <iostream>
#include "MusicComponent.hpp"

namespace BBM
{
    MusicComponent::MusicComponent(WAL::Entity &entity, std::string &musicPath)
        : WAL::Component(entity),
          _music(RAY::Audio::Music(musicPath))
    {
    }

    MusicComponent::MusicComponent(WAL::Entity &entity)
		: Component(entity),
          _music()
	{}

    WAL::Component *MusicComponent::clone(WAL::Entity &entity) const
	{
		return new MusicComponent(entity);
	}

	void MusicComponent::loadMusic(void)
    {   
        if (!this->_music.isPlaying())
            this->_music.play();
    }

    void MusicComponent::unloadMusic(void)
    {
        if (!this->_music.isPlaying())
            this->_music.stop();
    }

    void MusicComponent::pauseMusic(void)
    {
        this->_music.pause();
    }

	void MusicComponent::setVolume(float &volume)
    {
        if (volume >= 0)
            this->_music.setVolume(volume);
    }

	void MusicComponent::setPitch(float &pitch)
    {
        this->_music.setPitch(pitch);
    }

	bool MusicComponent::isPlaying(void)
    {
        return (this->_music.isPlaying());
    }

} // namespace WAL
