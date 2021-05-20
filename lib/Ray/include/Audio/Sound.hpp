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
            bool load(const std::string &path);

            //! @brief Unload Sound stream
            bool unload(void);

            //! @brief Check if Sound is playing
            bool isPlayin(void);

            //! @brief  Start Sound
            Sound &play(void);

            //! @brief Stop Sound playing
            Sound &stop(void);

            //! @brief Pause Sound playing
            Sound &pause(void);

            //! @brief Resume playing paused Sound
            Sound &resume(void);

            //! @brief Set volume for Sound (1.0 is max level)
            Sound &setVolume(float volume);

            // Set pitch for a Sound (1.0 is base level)
            Sound &setPitch(float pitch);

        private:
            ::Sound _sound;
    };
}

#endif /* !Sound_HPP_ */
