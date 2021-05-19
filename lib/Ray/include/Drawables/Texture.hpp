/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <raylib.h>
#include <string>
#include "Canvas.hpp"
#include "IRessource.hpp"

namespace RAY
{
    class Texture: public Canvas, IRessource {
        public:
            //! @brief Create an texture, loading a file
            //! @param filename: path to file to load
            Texture(const std::string &filename);

            //! @brief Create an texture, from an image
            //! @param image: reference to image to create texture from
            Texture(const Image &image);

            //! @brief A default copy constructor
            Texture(const Texture &) = default;

            //! @brief A default constructor, no ressources loaded
            Texture();

            //! @brief An image is assignable
            Texture &operator=(const Texture &) = default;
            
            //! @brief Texture destructor, will unload ressources
            ~Texture();

            //! @brief load ressources from file
            //! @param filename: path of input
            bool load(const std::string &filename);

            //! @brief unload ressources
            bool unload();

            //! @brief get image
            Image toImage(void) const;

            //! @return libray Texture struct
            const ::Texture &getTexture(void) const;

        protected:
        private:
            //! @brief Texture, really, that's just it...
            ::Texture _texture;
    };   
}

#endif /* !IMAGE_HPP_ */
