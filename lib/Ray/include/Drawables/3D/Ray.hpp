/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
    class Ray: public ADrawable3D
	{
        public:
            //! @brief Ray constructor
            //! @param startPosition position of top-left point  
            //! @param direction direction of the ray
            //! @param Color Color of the line  
            Ray(const Vector3 &startPosition, Vector3 direction, Color color);

            //! @brief A default copy constructor
            Ray(const Ray &) = default;

            //! @brief A line is assignable
            Ray &operator=(const Ray &) = default;

            //! @brief A default destructor
            ~Ray() = default;

            //! @return the length of the line
            int getLength(void) const;

            //! @return the start position of the line
            const Vector3 &getPosition(void) const;

            //! @return the end position of the line
            const Vector3 &getDirection(void) const;

            //! @brief Set start position
            Ray &setPosition(const Vector3 &startPosition);

            //! @brief Set end position
            Ray &setDirection(const Vector3 &dimensions);

            //! @brief Draw ray on window
            void drawOn(Window &);

        private:
            //! @brief start position
            Vector3 _startPosition;
            //! @brief direction
            Vector3 _direction;
    };
};

#endif /* !PIXEL_HPP_ */
