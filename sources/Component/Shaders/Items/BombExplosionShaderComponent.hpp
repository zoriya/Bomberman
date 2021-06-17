//
// Created by cbihan on 16/06/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace BBM
{
	class BombExplosionShaderComponent : public WAL::Component
	{
	public:
		//! @brief Explosion radius
		float explosionRadius = 4;
		//! @brief to have the shader move by the time
		float frameCounter = 0;
		//! @brief Transparency
		float alpha = 1;

		//! @brief max explosion radius
		static constexpr float maxRadius = 1.2;

		//! @brief The clock to use
		std::chrono::nanoseconds clock = 0ns;


		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief ctor
		explicit BombExplosionShaderComponent(WAL::Entity &entity);

		//! @brief Default copy ctor
		BombExplosionShaderComponent(const BombExplosionShaderComponent &) = default;

		//! @brief Default dtor
		~BombExplosionShaderComponent() override = default;

		//! @brief Default assignment operator
		BombExplosionShaderComponent &operator=(const BombExplosionShaderComponent &) = delete;
	};

}
