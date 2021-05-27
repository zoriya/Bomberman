/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "Audio/IAudio.hpp"

#include <raylib.h>


namespace RAY::Audio
{
	//! @brief A manager for sound stream
	class Sound: public IAudio {
		public:

			//! @brief Load Sound stream from file
			Sound(const std::string &path);

			//! @brief Default constructor
			Sound();

			//! @brief Default destructor
			~Sound();

			//! @brief A copy constructor constructor
			Sound(const Sound &sound) = default;

			//! @brief A Sound is assignable
			Sound &operator=(const Sound &sound) = default;

			//! @brief Load Sound stream from file
			bool load(const std::string &path) override;

			//! @brief Unload Sound stream
			bool unload(void) override;

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
			::Sound _sound;
	};
}

#endif /* !Sound_HPP_ */
