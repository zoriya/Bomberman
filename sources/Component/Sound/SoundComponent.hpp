//
// Created by Tom Augier on 05/06/2021
//

#pragma once

#include "Component/Component.hpp"
#include <map>
#include "Audio/Sound.hpp"

namespace BBM
{
	//! @brief A basic Sound component
	class SoundComponent : public WAL::Component
	{
	public:

		//! @brief All sounds of the player
		enum soundIndex {
			IDLE,
			JUMP,
			BOMB,
			MOVE,
			HURT,
			THROW,
			DEATH,
		};

		//! @brief to set what sound should be played
		void setIndex(soundIndex index);

		//! @brief to know which sound is selected
		soundIndex getIndex();

		//! @brief start sound
		void playSound();

		//! @brief stop sound
		void stopSound();

		//! @brief put Sound on hold
		void pauseSound();

		//! @brief set Sound volume
		void setVolume(float &);

		//! @brief set pitch volume
		void setPitch(float &);

		//! @brief is Sound playing
		bool isPlaying();

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;
		//! @brief Create a new SoundComponent at a certain Sound
		explicit SoundComponent(WAL::Entity &entity, const std::map<soundIndex, std::string> &);
		//! @brief A Sound component is copy constructable
		SoundComponent(const SoundComponent &) = default;
		//! @brief A default destructor
		~SoundComponent() override = default;
		//! @brief A Sound component is not assignable
		SoundComponent &operator=(const SoundComponent &) = delete;
		//! @brief Volume of the sounds
		float volume = 1;

	private:
		//! @brief Sounds of this entity
		std::map<soundIndex, std::unique_ptr<RAY::Audio::Sound>> _soundList;
		//! @brief map to know if sound is loaded
		std::map<soundIndex, bool> _isLoad;
		//! @brief All sounds path
		const std::map<soundIndex, std::string> _soundPath;
		//! SoundIndex
		soundIndex _soundIndex;

	};

} // namespace BBM