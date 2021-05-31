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
#include "Drawables/ADrawable2D.hpp"

namespace RAY
{
	class Image;
	//! @brief Object representation of a texture
	class Texture: public Drawables::ADrawable2D {
		public:
			//! @brief Create an texture, loading a file
			//! @param filename: path to file to load
			Texture(const std::string &filename);

			//! @brief A texture is not copy constructable
			Texture(const Texture &);

			//! @brief An image is assignable
			Texture &operator=(const Texture &);
			
			//! @brief Texture destructor, will unload ressources
			~Texture();

			//! @brief Draw drawble on window
			void drawOn(RAY::Window &) override;

			//! @brief Draw on image
			void drawOn(RAY::Image &image) override;

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
