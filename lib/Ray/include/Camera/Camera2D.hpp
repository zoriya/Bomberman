/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Camera2D
*/

#ifndef CAMERA2D_HPP_
#define CAMERA2D_HPP_

#include <raylib.h>
#include "Camera/ICamera.hpp"

namespace Ray::Camera {

    //! @brief Entity representing a Camera in 2D space
    class Camera2D: public ICamera {
        public:
            //! @brief 2D Camera constructor
            //! @param offset Camera offset (displacement from target)
            //! @param target Camera target (rotation and zoom origin
            //! @param rotation Camera rotation in degrees
            //! @param zoom Camera zoom (scaling), should be 1.0f by default
            Camera2D(Vector2 offset, Vector2 target, float rotation, float zoom);

            //! @brief A copy constructor
            Camera2D(const Camera2D &);

            ~Camera2D() = default;

            //! @brief A Camera is assignable
            Camera2D &operator=(const Camera2D &) = default;

            //! @brief Set Offset
            Camera2D &setOffset(Vector2 offset);
            //! @brief Set target
            Camera2D &setTarget(Vector2 target);
            //! @brief Set rotation
            Camera2D &setRotation(float rotation);
            //! @brief Set zoom
            Camera2D &setZoom(float zoom);

            //! @brief Get Offset
            const Vector2 &getOffset(void) const;
            //! @brief Get target
            const Vector2 &getTarget(void) const;
            //! @brief Get rotation
            float getRotation(void) const;
            //! @brief Get zoom
            float getZoom(void) const;

            //! @brief Returns camera 2d transform matrix
            Matrix getMatrix(void) const;

        private:
            ::Camera2D _camera;
    };
}

#endif /* !CAMERA2D_HPP_ */
