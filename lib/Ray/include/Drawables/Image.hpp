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
#include "Canvas.hpp"

namespace Ray
{
    class Image: public Canvas {
        public:
            //! @brief Create an image, loading a file
            //! @param filename: path to file to load
            Image(const std::string &filename);

            //! @brief A default copy constructor
            Image(const Image &);

            //! @brief A default constructor, no ressources loaded
            Image();

            //! @brief An image is assignable
            Image &operator=(const Image &) = default;
            
            //! @brief Image destructor, will unload ressources
            ~Image();

            //! @brief load ressources from file
            //! @param filename: path of input
            bool load(const std::string &filename);

            //! @brief export to file
            //! @param outputPath: path of output
            bool exportTo(const std::string &outputPath);

            //! @brief unload ressources
            bool unload();

            //! @brief get image
            const ::Image &getImage(void) const;


//! @brief draw rectangle
            virtual void draw(const Drawable2D::Rectangle &) = 0;

            //! @brief draw Line
            virtual void draw(const Drawable2D::Line &) = 0;

            //! @brief draw Point
            virtual void draw(const Drawable2D::Point &) = 0;

            //! @brief draw Circle
            virtual void draw(const Drawable2D::Circle &) = 0;

            //! @brief draw Text
            virtual void draw(const Drawable2D::Text &) = 0;
    
            //! @brief draw Triangle
            virtual void draw(const Drawable2D::Triangle &) = 0;

            //! @brief draw Line
            virtual void draw(const Drawable3D::Line &) = 0;

            //! @brief draw Point
            virtual void draw(const Drawable3D::Point &) = 0;

            //! @brief draw Circle
            virtual void draw(const Drawable3D::Circle &) = 0;

            //! @brief draw Cylinder
            virtual void draw(const Drawable3D::Cylinder &) = 0;

            //! @brief draw Plane
            virtual void draw(const Drawable3D::Plane &) = 0;

            //! @brief draw Ray
            virtual void draw(const Drawable3D::Ray &) = 0;
    
            //! @brief draw Sphere
            virtual void draw(const Drawable3D::Sphere &) = 0;

            //! @brief draw Triangle
            virtual void draw(const Drawable3D::Triangle &) = 0;

        protected:
        private:
            //! @brief Image, really, that's just it...
            ::Image _image;
    };   
}

#endif /* !IMAGE_HPP_ */
