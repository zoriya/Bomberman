/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Font
*/

#ifndef FONT_HPP_
#define FONT_HPP_

#include <raylib.h>
#include <string>

namespace RAY
{
    class Font {
        public:
            //! @brief Create an font, loading a file
            //! @param filename: path to file to load
            Font(const std::string &filename);

            //! @brief A default copy constructor
            Font(const Font &);

            //! @brief A default constructor, no ressources loaded
            Font();

            //! @brief An image is assignable
            Font &operator=(const Font &) = default;
            
            //! @brief Unload font at destruction
            ~Font();

            //! @brief load font from file
            //! @param filename: path of input
            bool load(const std::string &filename);

            //! @brief unload ressources
            bool unload();


        protected:
        private:
            //! @brief Font, really, that's just it...
            ::Font _font;
    };   
}

#endif