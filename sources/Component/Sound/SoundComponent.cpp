//
// Created by Tom Augier on 05/06/2021
//

#include <iostream>
#include <memory>
#include "SoundComponent.hpp"

namespace BBM
{	
	float SoundComponent::volume = 0.75;

	SoundComponent::SoundComponent(WAL::Entity &entity, 
		                           const std::map<SoundComponent::SoundIndex, std::string> &soundPath,
								   bool isLonely)
		: WAL::Component(entity),
		  _soundIndex(IDLE),
		  _soundPath(soundPath),
		  _isLonely(isLonely)
	{
		for (int i = 0; i <= DEATH; i++) {
			this->_isSoundLoad[static_cast<SoundIndex>(i)] = false;
		}
		for (auto &soundPath : soundPath)
		{
			this->_isSoundLoad[soundPath.first] = true;
			this->_soundList[soundPath.first] = std::make_unique<RAY::Audio::Sound>(soundPath.second, this->_isLonely);	
		}
	}

	WAL::Component *SoundComponent::clone(WAL::Entity &entity) const
	{
		return new SoundComponent(entity, this->_soundPath);
	}

	void SoundComponent::playSound()
	{   
		if (!this->_isSoundLoad.at(this->_soundIndex))
			return;
		if (!this->_soundList[this->_soundIndex].get()->isPlaying())
			this->_soundList[this->_soundIndex].get()->play();
	}

	void SoundComponent::stopSound()
	{
		if (!this->_isSoundLoad.at(this->_soundIndex))
			return;
		if (this->_soundList[this->_soundIndex].get()->isPlaying())
			this->_soundList[this->_soundIndex].get()->stop();
	}

	void SoundComponent::pauseSound()
	{
		if (!this->_isSoundLoad.at(this->_soundIndex))
			return;
		this->_soundList[this->_soundIndex].get()->pause();
	}

	void SoundComponent::setVolume(float volumeUpdate)
	{
		if (volumeUpdate >= 0 && volumeUpdate <= 1) {
			this->volume = volumeUpdate;
			for (auto &sound : _soundList)
				sound.second->setVolume(volume);
		}
	}

	void SoundComponent::setPitch(float pitch)
	{
		if (!this->_isSoundLoad.at(this->_soundIndex))
			return;
		this->_soundList[this->_soundIndex].get()->setPitch(pitch);
	}

	bool SoundComponent::isPlaying()
	{
		if (!this->_isSoundLoad.at(this->_soundIndex))
			return (false);
		return (this->_soundList[this->_soundIndex].get()->isPlaying());
	}
	
	void SoundComponent::setIndex(SoundIndex index)
	{
		this->_soundIndex = index;
	}

	SoundComponent::SoundIndex SoundComponent::getIndex()
	{
		return (this->_soundIndex);
	}

	void SoundComponent::turnDownVolume()
	{
		this->setVolume(SoundComponent::volume - 0.1);
	}

	void SoundComponent::turnUpVolume()
	{
		this->setVolume(SoundComponent::volume + 0.1);
	}

} // namespace WAL
