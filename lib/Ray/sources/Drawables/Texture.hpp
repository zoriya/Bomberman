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
#include "Drawables/2D/Rectangle.hpp"

namespace RAY
{
	//! @brief Object representation of a texture
	class Texture: public Drawables::Drawables2D::Rectangle {
		public:
			//! @brief Create an texture, loading a file
			//! @param filename: path to file to load
			Texture(const std::string &filename);

			//! @brief A texture is copy constructable
			Texture(const Texture &) = default;

			//! @brief A textrue can be loaded from an image
			Texture(const Image &);

			//! @brief An texture is assignable
			Texture &operator=(const Texture &) = default;
			
			//! @brief Texture destructor, will not unload ressources
			~Texture() = default;

			//! @brief draw texture on a window
			void drawOn(RAY::Window &) override;
	
			//! @brief Load texture from file, lets one use one entity for multiple files
			Texture &use(const std::string &filename);

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
