//
// Created by cbihan on 15/06/2021.
//

#pragma once

#include "ShaderSystem.hpp"
#include "System/System.hpp"
#include "Wal.hpp"

namespace BBM
{
	class ShaderModelSystem : public WAL::System<ShaderComponentModel>
	{
	public:

		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<ShaderComponentModel> &entity) override;

		//! @brief ctor
		explicit ShaderModelSystem(WAL::Wal &wal);
		//! @brief Default copy ctor
		ShaderModelSystem(const ShaderModelSystem &) = default;
		//! @brief Default dtor
		~ShaderModelSystem() override = default;
		//! @brief A render screen system can't be assigned.
		ShaderModelSystem &operator=(const ShaderModelSystem &) = delete;
	};
}