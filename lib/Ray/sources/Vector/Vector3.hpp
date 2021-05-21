/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Vector2
*/

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include "Vector/Vector2.hpp"

namespace RAY {
	//! @brief A Three-dimensionnal Vector data type.
	struct Vector3: public Vector2
	{
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
		
		//! @brief A RAY Vector3 is cast-able in libray's Vector3
		operator ::Vector3() const;
		
		//! @brief Z value of vector
		float z;
	};
}


#endif /* !VECTOR2_HPP_ */
