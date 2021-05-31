

#pragma once
#include "Models/Vector3.hpp"

namespace BBM {
    class Button {
    public:
		//! @brief A default constructor
		Button(void);
		//! @brief A button is copy constructable
		Button(const Button &) = default;
		//! @brief A default destructor
		~Button() = default;
		//! @brief A button system is assignable.
		Button &operator=(const Button &) = default;
    }
};
