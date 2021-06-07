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
#include "Texture.hpp"
#include "Utils/Cache.hpp"
#include "Drawables/2D/Rectangle.hpp"

namespace RAY
{
	//! @brief Object representation of a framebuffer
	class Image: public Drawables::Drawables2D::Rectangle {
		public:
			//! @brief Create an image, loading a file
			//! @param filename: path to file to load
			Image(const std::string &filename);

			//! @brief A default copy constructor
			Image(const Image &image) = default;

			//! @brief An image is assignable
			Image &operator=(const Image &image) = default;
			
			//! @brief Image destructor, will unload ressources
			~Image() override = default;

			//! @brief export to file
			//! @param outputPath: path of output
			bool exportTo(const std::string &outputPath);

			//! @brief draw drawable on image
			void draw(Drawables::ADrawable2D &);

			//! @brief Draw image on window
			void drawOn(RAY::Window &) override;

			//! @brief Draw image on another image
			void drawOn(RAY::Image &image) override;
			
			//! @brief Resize image;
			void resize(const RAY::Vector2 &dimensions);

		private:
			//! @brief Image, really, that's just it...
			std::shared_ptr<::Image> _image;

			static Cache<::Image> _imagesCache;

		
		INTERNAL:
			//! @brief get image
			operator ::Image() const;
			operator ::Image *();
	};   
}

#endif /* !IMAGE_HPP_ */
