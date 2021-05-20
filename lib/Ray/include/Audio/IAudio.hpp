/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include "IRessource.hpp"
#include <string>

namespace RAY::Audio
{
    class IAudio: public IRessource {
        public:
            virtual ~IAudio() = 0;

             //! @brief Load Audio stream from file
            bool load(const std::string &path);

            //! @brief Unload audio stream
            bool unload(void);

            //! @brief Check if audio is playing
            bool isPlaying(void);

            //! @brief  Start audio
            IAudio &play(void);

            //! @brief Stop audio playing
            IAudio &stop(void);

            //! @brief Pause audio playing
            IAudio &pause(void);

            //! @brief Resume playing paused audio
            IAudio &resume(void);

            //! @brief Set volume for audio (1.0 is max level)
            IAudio &setVolume(float volume);

            // Set pitch for a audio (1.0 is base level)
            IAudio &setPitch(float pitch);

        protected:
        private:
    };
}

#endif /* !AUDIO_HPP_ */
