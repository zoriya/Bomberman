//
// Created by cbihan on 26/05/2021.
//

#pragma once

#include "Vector/Vector3.hpp"
#include "Models/Vector3.hpp"

namespace BBM
{
	struct Utils
	{
		//! @brief Convert BBM Vector3f to RAY Vector3
		static RAY::Vector3 toRAY(const BBM::Vector3f &wal);

		//! @brief default ctor
		Utils() = default;
		//! @brief Default copy ctor
		Utils(const Utils &) = default;
		//! @brief Default dtor
		~Utils() = default;
		//! @brief Default assignment operator
		Utils &operator=(const Utils &) = default;
	};
}