//
// Created by cbihan on 26/05/2021.
//

#include "Vector3.hpp"

namespace BBM
{
	RAY::Vector3 operator*(const Vector3f &v)
	{
		return {v.x, v.y, v.z};
	}
}