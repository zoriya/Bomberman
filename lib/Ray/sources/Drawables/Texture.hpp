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
#include "Utils/Cache.hpp"

namespace RAY
{
	//! @brief Object representation of a texture
	class Texture {
		public:
			//! @brief Create an texture, loading a file
			//! @param filename: path to file to load
			//! @param lonely: should be set to true if the entity's loaded data must be independant from others
			Texture(const std::string &filename, bool lonely = false);

			//! @brief A texture is copy constructable
			Texture(const Texture &) = default;

			//! @brief A textrue can be loaded from an image
			Texture(const Image &);

			//! @brief An texture is assignable
			Texture &operator=(const Texture &) = default;
			
			//! @brief Texture destructor, will not unload ressources
			~Texture() = default;

		protected:
		private:
			//! @brief Texture, really, that's just it...
			std::shared_ptr<::Texture> _texture;

			//! @brief path to the file the texture is loaded from
			std::string _resourcePath;

			static Cache<::Texture> _texturesCache; 

		INTERNAL:
			//! @return libray Texture struct
			operator ::Texture() const;
	};   
}

#endif /* !IMAGE_HPP_ */
