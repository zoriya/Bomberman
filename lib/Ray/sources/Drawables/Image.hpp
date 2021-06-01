/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <raylib.h>
#include <string>
#include "Vector/Vector2.hpp"

namespace RAY
{
	namespace Drawables {
		class ADrawable2D;
	}
	class Texture;
	//! @brief Object representation of a framebuffer
	class Image {
		public:
			//! @brief Create an image, loading a file
			//! @param filename: path to file to load
			Image(const std::string &filename);

			//! @brief Create an image, using data from a texure
			//! @param texture: texture to extract data from
			Image(Texture &texture);

			//! @brief A default copy constructor
			Image(const Image &image) = delete;

			//! @brief An image is assignable
			Image &operator=(const Image &image) = delete;
			
			//! @brief Image destructor, will unload ressources
			~Image();

			//! @brief export to file
			//! @param outputPath: path of output
			bool exportTo(const std::string &outputPath);

			//! @brief resize image dimension
			Image &resize(const RAY::Vector2 &dimensions);

			//! @brief draw drawable
			void draw(Drawables::ADrawable2D &);

		private:
			//! @brief Image, really, that's just it...
			::Image _image;
		
		INTERNAL:
			//! @brief get image
			operator ::Image() const;
			operator ::Image *();
	};   
}

#endif /* !IMAGE_HPP_ */
