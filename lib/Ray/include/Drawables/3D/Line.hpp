/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef LINE3D_HPP_
#define LINE3D_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
    class Line: public ADrawable3D
	{
        public:
            //! @brief Line constructor
            //! @param startPosition position of top-left point  
            //! @param startPosition position of bottom-rigth point  
            //! @param Color Color of the line  
            Line(const Vector3 &startPosition, Vector3 endPosition, Color color);

            //! @brief A default copy constructor
            Line(const Line &) = default;

            //! @brief A line is assignable
            Line &operator=(const Line &) = default;

            //! @brief A default destructor
            ~Line() = default;

            //! @return the length of the line
            int getLength(void) const;

            //! @return the start position of the line
            const Vector3 &getStartPosition(void) const;

            //! @return the end position of the line
            const Vector3 &getEndPosition(void) const;

            //! @brief Set start position
            Line &setStartPosition(const Vector3 &startPosition);

            //! @brief Set end position
            Line &setEndPosition(const Vector3 &endPosition);

            //! @brief Draw line on window
            void drawOn(Window &);

        private:
            //! @brief start position
            Vector3 _startPosition;
            //! @brief end position
            Vector3 _endPosition;
    };
};

#endif /* !PIXEL_HPP_ */
