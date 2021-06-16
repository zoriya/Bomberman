//
// Created by cbihan on 15/06/2021.
//

#pragma once

#include "Component/Shaders/ShaderComponent.hpp"
#include "System/System.hpp"
#include "Wal.hpp"

namespace BBM
{
	class ShaderDrawable2DSystem : public WAL::System<ShaderComponentDrawable2D>
	{
	public:

		//! @inherit
		void onUpdate(WAL::ViewEntity<ShaderComponentDrawable2D> &entity, std::chrono::nanoseconds dtime) override;

		//! @brief ctor
		explicit ShaderDrawable2DSystem(WAL::Wal &wal);
		//! @brief Default copy ctor
		ShaderDrawable2DSystem(const ShaderDrawable2DSystem &) = default;
		//! @brief Default dtor
		~ShaderDrawable2DSystem() override = default;
		//! @brief A render screen system can't be assigned.
		ShaderDrawable2DSystem &operator=(const ShaderDrawable2DSystem &) = delete;
	};
}