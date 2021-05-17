/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Canvas
*/

#ifndef Canvas_HPP_
#define Canvas_HPP_

#include "Drawables/ADrawable2D.hpp"
#include "Drawables/2D/Circle.hpp"
#include "Drawables/2D/Line.hpp"
#include "Drawables/2D/Point.hpp"
#include "Drawables/2D/Text.hpp"
#include "Drawables/2D/Triangle.hpp"
#include "Drawables/2D/Rectangle.hpp"
#include "Drawables/ADrawable3D.hpp"
#include "Drawables/3D/Circle.hpp"
#include "Drawables/3D/Cylinder.hpp"
#include "Drawables/3D/Line.hpp"
#include "Drawables/3D/Plane.hpp"
#include "Drawables/3D/Point.hpp"
#include "Drawables/3D/Ray.hpp"
#include "Drawables/3D/Sphere.hpp"
#include "Drawables/3D/Triangle.hpp"

namespace RAY {
    class Canvas {
        public:
            //! @brief A default destructor
            virtual ~Canvas() = 0;

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
    };
}

#endif /* !Canvas_HPP_ */
