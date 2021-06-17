//
// Created by cbihan on 15/06/2021.
//

#pragma once

#include "Component/Shaders/ShaderComponent.hpp"
#include "System/System.hpp"

namespace BBM
{
	class ShaderSystem : public WAL::System<ShaderComponent>
	{
	public:

		//! @inherit
		void onUpdate(WAL::ViewEntity<ShaderComponent> &entity, std::chrono::nanoseconds dtime) override;

		//! @brief ctor
		explicit ShaderSystem(WAL::Wal &wal);
		//! @brief Default copy ctor
		ShaderSystem(const ShaderSystem &) = default;
		//! @brief Default dtor
		~ShaderSystem() override = default;
		//! @brief A render screen system can't be assigned.
		ShaderSystem &operator=(const ShaderSystem &) = delete;
	};
}