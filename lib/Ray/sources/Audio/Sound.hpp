/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "Audio/IAudio.hpp"
#include "Utils/Cache.hpp"
#include <raylib.h>


namespace RAY::Audio
{
	//! @brief A manager for sound stream
	class Sound: public IAudio {
		public:

			//! @brief Load Sound stream from file
			//! @param lonely: should be set to true if the entity's loaded data must be independant from others
			Sound(const std::string &path, bool lonely = false);

			//! @brief Default destructor
			~Sound() = default;

			//! @brief A copy constructor constructor
			Sound(const Sound &sound) = default;

			//! @brief A Sound is assignable
			Sound &operator=(const Sound &sound) = default;

			//! @brief Check if Sound is playing
			bool isPlaying(void) override;

			//! @brief  Start Sound
			Sound &play(void) override;

			//! @brief Stop Sound playing
			Sound &stop(void) override;

			//! @brief Pause Sound playing
			Sound &pause(void) override;

			//! @brief Resume playing paused Sound
			Sound &resume(void) override;

			//! @brief Set volume for Sound (1.0 is max level)
			Sound &setVolume(float volume) override;

			// Set pitch for a Sound (1.0 is base level)
			Sound &setPitch(float pitch) override;

		private:
			std::shared_ptr<::Sound> _sound;

			static RAY::Cache<::Sound> _soundsCache;
	};
}

#endif /* !Sound_HPP_ */
