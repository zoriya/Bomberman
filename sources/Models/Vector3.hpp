//
// Created by Zoe Roux on 5/17/21.
//


#pragma once

#include <iostream>
#include <cmath>

namespace BBM
{
	//! @brief A Vector3 data type. (templated to allow any kind of vector3)
	template<typename T>
	class Vector3
	{
	public:
		//! @brief The x value of the vector
		T x;
		//! @brief The y value of the vector
		T y;
		//! @brief The y value of the vector
		T z;

		//! @brief Create a new nil vector3.
		Vector3()
			: x(0), y(0), z(0)
		{}

		//! @brief Create a new vector3 representing a specific coordinate.
		Vector3(T x, T y, T z)
			: x(x), y(y), z(z)
		{}

		//! @brief A default destructor
		~Vector3() = default;

		bool operator==(const Vector3<T> &other) const
		{
			return this->x == other.x && this->y == other.y && this->z == other.z;
		}

		bool operator!=(const Vector3<T> &other) const
		{
			return !this->operator==(other);
		}

		template<typename T2>
		Vector3<T> &operator+=(const Vector3<T2> &vec)
		{
			this->x += vec.x;
			this->y += vec.y;
			this->z += vec.z;
			return *this;
		}

		template<typename T2>
		Vector3<T> operator+(const Vector3<T2> &vec) const
		{
			return Vector3<T>(this->x + vec.x, this->y + vec.y, this->z + vec.z);
		}

		template<typename T2>
		Vector3<T> &operator-=(const Vector3<T2> &vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
			this->z -= vec.z;
			return *this;
		}

		template<typename T2>
		Vector3<T> &operator*=(T2 d)
		{
			this->x *= d;
			this->y *= d;
			this->z *= d;
			return *this;
		}

		template<typename T2>
		Vector3<T> operator*(T2 d) const
		{
			return Vector3<T>(this->x * d, this->y * d, this->z * d);
		}

		template<typename T2>
		Vector3<T> operator*(const Vector3<T2> &b) const
		{
			return Vector3<T>(this->x * b.x, this->y * b.y, this->z * b.z);
		}

		template<typename T2>
		Vector3<T> operator/=(const Vector3<T2> &b)
		{
			this->x /= b.x;
			this->y /= b.y;
			this->z /= b.z;
			return this;
		}

		template<typename T2>
		Vector3<T> operator/(const Vector3<T2> &b) const
		{
			return Vector3<T>(this->x / b.x, this->y / b.y, this->z / b.z);
		}

		template<typename T2>
		Vector3<T> operator/=(T2 b)
		{
			this->x /= b;
			this->y /= b;
			this->z /= b;
			return this;
		}

		template<typename T2>
		Vector3<T> operator/(T2 b) const
		{
			return Vector3<T>(this->x / b, this->y / b, this->z / b);
		}

		template<typename T2>
		double distance(const Vector3<T2> &o) const
		{
			return std::sqrt(std::pow(this->x - o.x, 2) + std::pow(this->y - o.y, 2) + std::pow(this->z - o.z, 2));
		}

		double magnitude() const
		{
			return (std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2), std::pow(this->z, 2)));
		}

		Vector3<T> normalize()
		{
			double mag = this->magnitude();

			this->x /= mag;
			this->y /= mag;
			this->z /= mag;
			return *this;
		}

		Vector3<T> normalized() const
		{
			T mag = this->magnitude();

			return Vector3<T>(this->x / mag, this->y / mag, this->z / mag);
		}

		Vector3<T> projection(const Vector3<T> &point) const
		{
			return (point * this) / std::pow(this->magnitude(), 2) * this;
		}
	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<unsigned> Vector3u;
	typedef Vector3<int> Vector3i;
} // namespace WAL

template<typename T>
std::ostream &operator<<(std::ostream &s, const BBM::Vector3<T> &v)
{
	s << "Vector3<" << typeid(T).name() << ">("<< v.x << ", " << v.y << ", " << v.z << ")";
	return s;
}