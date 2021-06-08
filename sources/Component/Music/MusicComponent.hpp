//
// Created by Tom Augier on 05/06/2021
//

#pragma once

#include "Component/Component.hpp"
#include <map>
#include "Audio/Music.hpp"

namespace BBM
{
	//! @brief A basic Music component
	class MusicComponent : public WAL::Component
	{
	public:
		//! @brief start music
		void playMusic();

		//! @brief stop music
		void stopMusic();

		//! @brief put music on hold
		void pauseMusic();

		//! @brief set music volume
		void setVolume(float &);

		//! @brief set pitch volume
		void setPitch(float &);

		//! @brief is music playing
		bool isPlaying(void);
		
		void updateMusicStream(void);
		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;
		//! @brief Create a new MusicComponent at a certain Music
		explicit MusicComponent(WAL::Entity &entity, const std::string &musicPath);
		//! @brief A Music component is copy constructable
		MusicComponent(const MusicComponent &) = default;
		//! @brief A default destructor
		~MusicComponent() override = default;
		//! @brief A Music component is not assignable
		MusicComponent &operator=(const MusicComponent &) = delete;
		//! @brief Volume of the muisc
		float volume = 1;
	private:
		//! @brief music of this entity
		RAY::Audio::Music _music;
		//! @brief patht to the music assets
		const std::string _musicPath;
	};

} // namespace BBM