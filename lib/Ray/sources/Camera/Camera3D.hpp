/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Camera3D
*/

#ifndef CAMERA3D_HPP_
#define CAMERA3D_HPP_

#include <raylib.h>
#include "Camera/ICamera.hpp"
#include "Camera/CameraProjection.hpp"
#include "Camera/CameraMode.hpp"

namespace RAY::Camera {

	//! @brief Entity representing a Camera in 3D space
	class Camera3D: public ICamera {
		public:
			//! @brief 3D Camera constructor
			//! @param position Camera position
			//! @param target Camera target it looks-at
			//! @param up Camera up vector (rotation over its axis)
			//! @param fovy Camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic
			//! @param projection Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
			Camera3D(const Vector3 &position, const Vector3 &target, const Vector3 &up, float fovy, Projection projection);

			//! @brief A copy constructor
			Camera3D(const Camera3D &) = default;

			~Camera3D() override = default;

			//! @brief A Camera is assignable
			Camera3D &operator=(const Camera3D &) = default;

			//! @brief Set Position
			void setPosition(const Vector3 &Position);
			//! @brief Set target
			void setTarget(const Vector3 &target);
			//! @brief Set up
			void setUp(const Vector3 &up);
			//! @brief Set fovy
			void setFovy(float fovy);
			//! @brief Set Projection
			void setProjection(Projection projection);

			//! @brief Get Position
			const Vector3 &getPosition(void) const;
			//! @brief Get target
			const Vector3 &getTarget(void) const;
			//! @brief Get up
			const Vector3 &getUp(void) const;
			//! @brief Get Fovy
			float getFovy(void) const;
			//! @brief Get projection
			Projection getProjection(void) const;

			//! @brief Returns camera 3d transform matrix
			Matrix getMatrix(void) const override;

			// Set camera mode (multiple camera modes available)
			void setMode(Mode mode);

		private:
			::Camera3D _camera;
			Mode _mode;
		
		INTERNAL:
			//! @brief get camera struct
			operator ::Camera3D() const;
	};
}

#endif /* !CAMERA3D_HPP_ */
