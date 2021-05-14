/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <raylib.h>
#include <Vector.hpp>
#include "Drawables/Basic/Circle.hpp"
#include "Drawables/Basic/Line.hpp"
#include "Drawables/Basic/Rectangle.hpp"
#include "Drawables/Basic/Point.hpp"

namespace Ray {
    class Drawable
	{
        public:
            //! @brief Drawable constructor
            //! @param poition position of top-left point (in percentage)
            //! @param Color Color of the color  
            Drawable(Vector2 position, Color color);
            //! @brief Drawable constructor
            //! @param x x-position of top-left point (in percentage) 
            //! @param y y-position of top-left point (in percentage)
            //! @param Color Color of the color  
            Drawable(int x, int y, Color color);

            //! @brief A default copy constructor
            Drawable(const Drawable &) = default;

            //! @brief A default destructor
            virtual ~Drawable() = 0;

            //! @return the top-left position of the drawable
            const Vector2 &getPosition(void) const;

            //! @return the color of the drawable
            const Color &getColor(void) const;

            //! @brief set Top-left position
            Drawable &setPosition(const Vector2 &position);
            
            //! @brief set Top-left position
            Drawable &setPosition(int x, int y);
            
            //! @brief set color
            Drawable &setColor(const Color &color) const;

        private:
            //! @brief Top-left position (in percentage)
            Vector2 _position;
            //! @brief Color of the drawable
            Color _color;

    };
};

#endif /* !DRAWABLE_HPP_ */
