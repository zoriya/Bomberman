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

namespace RAY::Camera {

	//! @brief Entity representing a Camera in 2D space
	class Camera2D: public ICamera {
		public:
			//! @brief 2D Camera constructor
			//! @param offset Camera offset (displacement from target)
			//! @param target Camera target (rotation and zoom origin
			//! @param rotation Camera rotation in degrees
			//! @param zoom Camera zoom (scaling), should be 1.0f by default
			Camera2D(const Vector2 &offset, const Vector2 &target, float rotation, float zoom = 1);

			//! @brief A copy constructor
			Camera2D(const Camera2D &) = default;

			~Camera2D() override = default;

			//! @brief A Camera is assignable
			Camera2D &operator=(const Camera2D &) = default;

			//! @brief Set Offset
			void setOffset(const Vector2 &offset);
			//! @brief Set target
			void setTarget(const Vector2 &target);
			//! @brief Set rotation
			void setRotation(float rotation);
			//! @brief Set zoom
			void setZoom(float zoom);

			//! @brief Get Offset
			const Vector2 &getOffset(void) const;
			//! @brief Get target
			const Vector2 &getTarget(void) const;
			//! @brief Get rotation
			float getRotation(void) const;
			//! @brief Get zoom
			float getZoom(void) const;

			//! @brief Returns camera 2d transform matrix
			Matrix getMatrix(void) const override;

		private:
			::Camera2D _camera;

		INTERNAL:
			//! @brief get camera struct
			operator ::Camera2D() const;
	};
}

#endif /* !CAMERA2D_HPP_ */
