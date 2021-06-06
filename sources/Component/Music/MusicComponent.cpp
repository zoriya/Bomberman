/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** MusicComponent
*/

#include "MusicComponent.hpp"


namespace BBM
{
    MusicComponent::MusicComponent(WAL::Entity &entity, std::string &path)
        : WAL::Component(entity),
          _musicPath(path)
    {}

    WAL::Component *MusicComponent::clone(WAL::Entity &entity) const
	{
		return new MusicComponent(entity);
	}


	void MusicComponent::loadMusic(void)
    {
        this->_music = RAY::Audio::Music(this->_musicPath);
        this->_music.play();
    }

    void MusicComponent::unloadMusic(void)
    {
        this->_music.stop();
    }

    void MusicComponent::pauseMusic(void)
    {
        this->_music.pause();
    }

	void MusicComponent::setVolume(float &volume)
    {
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
