//
// Created by cbihan on 18/06/2021.
//

#pragma once

#include <Component/Component.hpp>
#include <chrono>

using namespace std::chrono_literals;

namespace BBM
{
	class AlphaVarShaderComponent : public WAL::Component
	{
	public:
		//! @brief Transparency
		float alpha = 1;

		//! @brief minimum transparency
		float minAlpha = 0.2;
		//! @brief maximum transparency
		float maxAlpha = 1;
		//! @brief inital step value
		float initalStepValue = 0.04;
		//! @brief how fast the alpha will vary
		float step = 0.04;
		//! @brief if the alpha should increase or decrease
		float balance = -1;

		//! @brief The clock to use
		std::chrono::nanoseconds clock = 0ns;


		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief ctor
		explicit AlphaVarShaderComponent(WAL::Entity &entity);

		//! @brief Default copy ctor
		AlphaVarShaderComponent(const AlphaVarShaderComponent &) = default;

		//! @brief Default dtor
		~AlphaVarShaderComponent() override = default;

		//! @brief Default assignment operator
		AlphaVarShaderComponent &operator=(const AlphaVarShaderComponent &) = delete;
	};

}