/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Music
*/

#ifndef Music_HPP_
#define Music_HPP_

#include "Audio/IAudio.hpp"

#include <raylib.h>


namespace RAY::Audio
{
    class Music: public IAudio {
        public:

            //! @brief Load Music stream from file
            Music(const std::string &path);

            //! @brief Default constructor
            Music();

            //! @brief Default destructor
            ~Music();

            //! @brief A copy constructor constructor
            Music(const Music &Music) = default;

            //! @brief A Music is assignable
            Music &operator=(const Music &Music) = default;

            //! @brief Load Music stream from file
            bool load(const std::string &path);

            //! @brief Unload Music stream
            bool unload(void);

            //! @brief Check if Music is playing
            bool isPlayin(void);

            //! @brief  Start Music
            Music &play(void);

            //! @brief Stop Music playing
            Music &stop(void);

            //! @brief Pause Music playing
            Music &pause(void);

            //! @brief Resume playing paused Music
            Music &resume(void);

            //! @brief Set volume for Music (1.0 is max level)
            Music &setVolume(float volume);

            // Set pitch for a Music (1.0 is base level)
            Music &setPitch(float pitch);

        private:
            ::Music _music;
    };
}

#endif /* !Music_HPP_ */
