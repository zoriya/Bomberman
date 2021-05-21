/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Cube
*/

#ifndef CUBE_HPP_
#define CUBE_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
	class Cube: public ADrawable3D
	{
		public:
			//! @brief Cube constructor
			//! @param position position of the cube 
			//! @param dimensions dimensions of the cube
			//! @param Color Color of the cube  
			Cube(const Vector3 &position, const Vector3 &dimensions, const Color &color);

			
			//! @brief A default copy constructor
			Cube(const Cube &) = default;

			//! @brief A circle is assignable
			Cube &operator=(const Cube &) = default;

			//! @brief A default destructor
			~Cube() = default;

			//! @return the position of the cube
			const Vector3 &getPosition(void) const;

			//! @return the dimensions of the cube
			const Vector3 &getDimensions(void) const;

			//! @brief set the dimensions of the cube
			Cube &setDimensions(const Vector3 &dimensions);

			//! @brief set the dimensions of the cube
			Cube &setPosition(const Vector3 &position);
		
			//! @brief Draw circle on window
			void drawOn(RAY::Window &) override;
		private:
			//! @brief Positon in space of the cube
			Vector3 _position;
			//! @brief Dimensions of the cube
			Vector3 _dimenstions;
	};
}

#endif /* !CUBE_HPP_ */
