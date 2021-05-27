//
// Created by Zoe Roux on 5/17/21.
//


#pragma once

#include <iostream>
#include <cmath>
#include "Vector/Vector2.hpp"

namespace BBM
{
	//! @brief A Vector2 data type. (templated to allow any kind of vector2)
	template<typename T>
	class Vector2
	{
	public:
		//! @brief The x value of the vector
		T x;
		//! @brief The y value of the vector
		T y;

		//! @brief Create a new nil vector2.
		Vector2()
			: x(0), y(0)
		{}

		//! @brief Create a new vector2 representing a specific coordinate.
		Vector2(T x, T y)
			: x(x), y(y)
		{}

		//! @brief A default destructor
		~Vector2() = default;

		bool operator==(const Vector2<T> &other) const
		{
			return this->x == other.x && this->y == other.y;
		}

		bool operator!=(const Vector2<T> &other) const
		{
			return !this->operator==(other);
		}

		template<typename T2>
		Vector2<T> &operator+=(const Vector2<T2> &vec)
		{
			this->x += vec.x;
			this->y += vec.y;
			return *this;
		}

		template<typename T2>
		Vector2<T> operator+(const Vector2<T2> &vec) const
		{
			return Vector2<T>(this->x + vec.x, this->y + vec.y);
		}

		template<typename T2>
		Vector2<T> &operator-=(const Vector2<T2> &vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
			return *this;
		}

		template<typename T2>
		Vector2<T> &operator*=(T2 d)
		{
			this->x *= d;
			this->y *= d;
			return *this;
		}

		template<typename T2>
		Vector2<T> operator*(T2 d) const
		{
			return Vector2<T>(this->x * d, this->y * d);
		}

		template<typename T2>
		Vector2<T> operator*(const Vector2<T2> &b) const
		{
			return Vector2<T>(this->x * b.x, this->y * b.y);
		}

		template<typename T2>
		Vector2<T> operator/=(const Vector2<T2> &b)
		{
			this->x /= b.x;
			this->y /= b.y;
			return this;
		}

		template<typename T2>
		Vector2<T> operator/(const Vector2<T2> &b) const
		{
			return Vector2<T>(this->x / b.x, this->y / b.y);
		}

		template<typename T2>
		Vector2<T> operator/=(T2 b)
		{
			this->x /= b;
			this->y /= b;
			return this;
		}

		template<typename T2>
		Vector2<T> operator/(T2 b) const
		{
			return Vector2<T>(this->x / b, this->y / b);
		}

		template<typename T2>
		double distance(const Vector2<T2> &o) const
		{
			return std::sqrt(std::pow(this->x - o.x, 2) + std::pow(this->y - o.y, 2));
		}

		double magnitude() const
		{
			return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
		}

		Vector2<T> normalize()
		{
			double mag = this->magnitude();

			this->x /= mag;
			this->y /= mag;
			return *this;
		}

		Vector2<T> normalized() const
		{
			T mag = this->magnitude();

			return Vector2<T>(this->x / mag, this->y / mag);
		}

		Vector2<T> projection(const Vector2<T> &point) const
		{
			return (point * this) / std::pow(this->magnitude(), 2) * this;
		}

		operator RAY::Vector2() const requires(std::is_same_v<T, float>)
		{
			return RAY::Vector2(this->x, this->y);
		}
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<unsigned> Vector2u;
	typedef Vector2<int> Vector2i;
}


template<typename T>
std::ostream &operator<<(std::ostream &s, const BBM::Vector2<T> &v)
{
	s << "Vector2<" << typeid(T).name() << ">("<< v.x << ", " << v.y << ")";
	return s;
}