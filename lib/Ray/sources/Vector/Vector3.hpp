/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Vector2
*/

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <raylib.h>

namespace RAY {
	//! @brief A Three-dimensionnal Vector data type.
	class Vector3
	{
		public:
			//! @brief Vector 3 constructor
			//! @param x x-value of vector, such as a width
			//! @param y y-value of vector, such as a height
			//! @param z z-value of vector, such as a depth
			Vector3(float x, float y, float z);
		
			//! @brief Vector 3 constructor
			//! @brief All values are set to zero
			Vector3();
		
			//! @brief A default Vector 3 copy-constructor
			Vector3(const Vector3 &) = default;

			//! @brief A Vector 3 constructor from libray's vector3
			Vector3(const ::Vector3 &);
		
			//! @brief A default Vector 3 destructor
			~Vector3() = default;
		
			//! @brief A Vector 3 is assignable
			Vector3 &operator=(const Vector3 &) = default;
		
		
			//! @brief X value of vector
			float x;
			//! @brief Y value of vector
			float y;
			//! @brief Z value of vector
			float z;

		INTERNAL:
			//! @brief A RAY Vector3 is cast-able in libray's Vector3
			operator ::Vector3() const;
	};
}


#endif /* !VECTOR2_HPP_ */
