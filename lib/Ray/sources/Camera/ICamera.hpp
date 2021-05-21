/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ICamera
*/

#ifndef ICAMERA_HPP_
#define ICAMERA_HPP_

#include "Matrix.hpp"

namespace RAY::Camera {
	//! @brief Interface for Cameras
	class ICamera {
		public:
			virtual ~ICamera() = default;

			virtual Matrix getMatrix() const = 0;
	};
}

#endif /* !ICAMERA_HPP_ */
