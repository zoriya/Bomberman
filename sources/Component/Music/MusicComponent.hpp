//
// Created by Zoe Roux on 5/17/21.
//

#pragma once

#include "Models/Vector3.hpp"
#include "Component/Component.hpp"
#include "Music.hpp"

namespace BBM
{
	//! @brief A basic Music component
	class MusicComponent : public WAL::Component
	{
	private:
		//! @brief music of this entity
		RAY::Audio::Music _music;
		//! @brief path to the music
        std::string _musicPath;	
		//! @brief Create a new MusicComponent linked to a specific entity
		explicit MusicComponent(WAL::Entity &entity);

	public:

		//! @brief load music
		void loadMusic();

		//! @brief unload music
        void unloadMusic();

		//! @brief put music on hold
		void pauseMusic();

		//! @brief set music volume
		void setVolume(float &);

		//! @brief set pitch volume
		void setPitch(float &);

		//! @brief is music playing
		bool isPlaying(void);

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;
		//! @brief Create a new MusicComponent at a certain Music
		MusicComponent(WAL::Entity &entity, std::string &musicPath);
		//! @brief A Music component is copy constructable
		MusicComponent(const MusicComponent &) = default;
		//! @brief A default destructor
		~MusicComponent() override = default;
		//! @brief A Music component is not assignable
		MusicComponent &operator=(const MusicComponent &) = delete;
	};
} // namespace WAL