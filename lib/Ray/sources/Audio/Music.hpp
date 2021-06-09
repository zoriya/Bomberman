/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include "Audio/IAudio.hpp"
#include <raylib.h>
#include "Utils/Cache.hpp"

namespace RAY::Audio
{
	//! @brief A manager for music stream
	class Music: public IAudio {
		public:

			//! @brief Load Music stream from file
			Music(const std::string &path);

			//! @brief Default destructor
			~Music() = default;

			//! @brief A copy constructor constructor
			Music(const Music &Music) = default;

			//! @brief A Music is assignable
			Music &operator=(const Music &Music) = default;

			//! @brief Check if Music is playing
			bool isPlaying(void) override;

			//! @brief  Start Music
			Music &play(void) override;

			//! @brief Stop Music playing
			Music &stop(void) override;

			//! @brief Pause Music playing
			Music &pause(void) override;

			//! @brief Resume playing paused Music
			Music &resume(void) override;

			//! @brief Set volume for Music (1.0 is max level)
			Music &setVolume(float volume) override;

			// Set pitch for a Music (1.0 is base level)
			Music &setPitch(float pitch) override;

			Music &updateMusicStream(void);

		private:
			std::shared_ptr<::Music> _music;

			static RAY::Cache<::Music> _musicsCache;
	};
}

#endif /* !Music_HPP_ */
