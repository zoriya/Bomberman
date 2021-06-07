//
// Created by Tom Augier on 05/06/2021
//

#include <iostream>
#include "MusicComponent.hpp"

namespace BBM
{
    MusicComponent::MusicComponent(WAL::Entity &entity, \
std::map<MusicComponent::musicIndex, std::string> &musicPath)
        : WAL::Component(entity),
          _musicIndex(IDLE)
    {
        for (int i = 0; i < DEATH + 1; i++) {
            if (musicPath.at(static_cast<musicIndex>(i)).empty()) {
                this->_isLoad[static_cast<musicIndex>(i)] = false;
            } else {
                this->_isLoad[static_cast<musicIndex>(i)] = true;
                this->_musicList[static_cast<musicIndex>(i)] = RAY::Audio::Music(musicPath.at(static_cast<musicIndex>(i)));
            }
        }
    }

    MusicComponent::MusicComponent(WAL::Entity &entity)
		: Component(entity),
		  _musicList(),
		  _musicIndex()
	{}

    WAL::Component *MusicComponent::clone(WAL::Entity &entity) const
	{
		return new MusicComponent(entity);
	}

	void MusicComponent::loadMusic(void)
    {   
        if (!this->_isLoad.at(this->_musicIndex))
            return;
        if (!this->_musicList[this->_musicIndex].isPlaying()) {
            std::cout << this->_musicIndex << std::endl;
            this->_musicList[this->_musicIndex].play();
        }
    }

    void MusicComponent::unloadMusic(void)
    {
        if (!this->_isLoad.at(this->_musicIndex))
            return;
        if (!this->_musicList[this->_musicIndex].isPlaying())
            this->_musicList[this->_musicIndex].stop();
    }

    void MusicComponent::pauseMusic(void)
    {
        if (!this->_isLoad.at(this->_musicIndex))
            return;
        this->_musicList[this->_musicIndex].pause();
    }

	void MusicComponent::setVolume(float &volume)
    {
        if (!this->_isLoad.at(this->_musicIndex))
            return;
        if (volume >= 0)
            this->_musicList[this->_musicIndex].setVolume(volume);
    }

	void MusicComponent::setPitch(float &pitch)
    {
        if (!this->_isLoad.at(this->_musicIndex))
            return;
        this->_musicList[this->_musicIndex].setPitch(pitch);
    }

	bool MusicComponent::isPlaying(void)
    {
        if (!this->_isLoad.at(this->_musicIndex))
            return (false);
        return (this->_musicList[this->_musicIndex].isPlaying());
    }
    
    void MusicComponent::setIndex(musicIndex index)
    {
        this->_musicIndex = index;
    }

    MusicComponent::musicIndex MusicComponent::getIndex(void)
    {
        return (this->_musicIndex);
    }

} // namespace WAL
