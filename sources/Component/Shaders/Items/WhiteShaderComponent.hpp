//
// Created by cbihan on 16/06/2021.
//

#pragma once


#include "Component/Component.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace BBM
{
	class WhiteShaderComponent : public WAL::Component
	{
	public:
		//! @brief Transparency
		float whiteValue = 0;

		//! @brief used to increase & decrease white value
		float balance = 1;

		//! @brief The clock to use
		std::chrono::nanoseconds clock = 0ns;


		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief ctor
		explicit WhiteShaderComponent(WAL::Entity &entity);

		//! @brief Default copy ctor
		WhiteShaderComponent(const WhiteShaderComponent &) = default;

		//! @brief Default dtor
		~WhiteShaderComponent() override = default;

		//! @brief Default assignment operator
		WhiteShaderComponent &operator=(const WhiteShaderComponent &) = delete;
	};

}

