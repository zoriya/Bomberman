/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_
#include <string>

namespace RAY::Audio
{
	//! @brief Interface for Audio ressources
	class IAudio {
		public:
			virtual ~IAudio() = default;

			//! @brief Check if audio is playing
			virtual bool isPlaying(void) = 0;

			//! @brief  Start audio
			virtual IAudio &play(void) = 0;

			//! @brief Stop audio playing
			virtual IAudio &stop(void) = 0;

			//! @brief Pause audio playing
			virtual IAudio &pause(void) = 0;

			//! @brief Resume playing paused audio
			virtual IAudio &resume(void) = 0;

			//! @brief Set volume for audio (1.0 is max level)
			virtual IAudio &setVolume(float volume) = 0;

			// Set pitch for a audio (1.0 is base level)
			virtual IAudio &setPitch(float pitch) = 0;

		protected:
		private:
	};
}

#endif /* !AUDIO_HPP_ */
