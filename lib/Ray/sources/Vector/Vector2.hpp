/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Vector2
*/

#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include <raylib.h>

namespace RAY {
	//! @brief A Two-dimensionnal Vector data type.
	class Vector2
	{
		public:
			//! @brief Vector 2 constructor
			//! @param x x-value of vector, such as a width
			//! @param y y-value of vector, such as a height
			Vector2(float x, float y);

			//! @brief Vector 2 constructor
			//! @brief All values are set to zero
			Vector2();

			//! @brief A default Vector 2 copy-constructor
			Vector2(const Vector2 &) = default;

			//! @brief A Vector 2 constructor from libray's vector2
			Vector2(const ::Vector2 &);

			//! @brief A default Vector 2 destructor
			~Vector2() = default;

			//! @brief A Vector 2 is assignable
			Vector2 &operator=(const Vector2 &) = default;

		
			//! @brief X value of vector
			float x;
			//! @brief Y value of vector
			float y;

		INTERNAL:
			//! @brief A RAY Vector2 is cast-able in libray's Vector2
			operator ::Vector2() const;
	};
}


#endif /* !VECTOR2_HPP_ */
