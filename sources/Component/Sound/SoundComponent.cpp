//
// Created by Tom Augier on 05/06/2021
//

#include <iostream>
#include <memory>
#include "SoundComponent.hpp"

namespace BBM
{
	SoundComponent::SoundComponent(WAL::Entity &entity, \
const std::map<SoundComponent::soundIndex, std::string> &soundPath)
		: WAL::Component(entity),
		  _soundIndex(IDLE),
		  _soundPath(soundPath)
	{
		this->volume = 1;
		for (int i = 0; i <= DEATH; i++) {
			if (soundPath.at(static_cast<soundIndex>(i)).empty()) {
				this->_isLoad[static_cast<soundIndex>(i)] = false;
			} else {
				this->_isLoad[static_cast<soundIndex>(i)] = true;
				this->_soundList[static_cast<soundIndex>(i)] = std::make_unique<RAY::Audio::Sound>(soundPath.at(static_cast<soundIndex>(i)));
			}
		}
	}

	float SoundComponent::volume;

	WAL::Component *SoundComponent::clone(WAL::Entity &entity) const
	{
		return new SoundComponent(entity, this->_soundPath);
	}

	void SoundComponent::playSound()
	{   
		if (!this->_isLoad.at(this->_soundIndex))
			return;
		if (!this->_soundList[this->_soundIndex].get()->isPlaying())
			this->_soundList[this->_soundIndex].get()->play();
	}

	void SoundComponent::stopSound()
	{
		if (!this->_isLoad.at(this->_soundIndex))
			return;
		if (this->_soundList[this->_soundIndex].get()->isPlaying())
			this->_soundList[this->_soundIndex].get()->stop();
	}

	void SoundComponent::pauseSound()
	{
		if (!this->_isLoad.at(this->_soundIndex))
			return;
		this->_soundList[this->_soundIndex].get()->pause();
	}

	void SoundComponent::setVolume(float &volumeUpdate)
	{
		if (!this->_isLoad.at(this->_soundIndex))
			return;
		if (volumeUpdate >= 0)
			this->volume = volumeUpdate;
			this->_soundList[this->_soundIndex].get()->setVolume(this->volume);
	}

	void SoundComponent::setPitch(float &pitch)
	{
		if (!this->_isLoad.at(this->_soundIndex))
			return;
		this->_soundList[this->_soundIndex].get()->setPitch(pitch);
	}

	bool SoundComponent::isPlaying()
	{
		if (!this->_isLoad.at(this->_soundIndex))
			return (false);
		return (this->_soundList[this->_soundIndex].get()->isPlaying());
	}
	
	void SoundComponent::setIndex(soundIndex index)
	{
		this->_soundIndex = index;
	}

	SoundComponent::soundIndex SoundComponent::getIndex()
	{
		return (this->_soundIndex);
	}

} // namespace WAL
