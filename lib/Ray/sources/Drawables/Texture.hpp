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

namespace RAY
{
	//! @brief Object representation of a texture
	class Texture {
		public:
			//! @brief Create an texture, loading a file
			//! @param filename: path to file to load
			Texture(const std::string &filename);

			//! @brief A texture is not constructable
			Texture(const Texture &);

			//! @brief A textrue can be loaded from an image
			Texture(const Image &);

			//! @brief An texture is assignable
			Texture &operator=(const Texture &);
			
			//! @brief Texture destructor, will unload ressources
			~Texture();

		protected:
		private:
			//! @brief Texture, really, that's just it...
			::Texture _texture;

			std::string _resourcePath;

		INTERNAL:
			//! @return libray Texture struct
			operator ::Texture() const;
	};   
}

#endif /* !IMAGE_HPP_ */
