//
// Created by Tom Augier on 05/06/2021
//

#pragma once

#include "System/System.hpp"
#include "Window.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include <Component/Controllable/ControllableComponent.hpp>
#include "Wal.hpp"

namespace BBM
{
	class CameraSystem : public WAL::System<CameraComponent, PositionComponent>
	{
	public:
		//! @brief A boolean indicating if the intro's animation has ended.
		bool hasEnded = false;

		//! @inherit
		void onUpdate(WAL::ViewEntity<CameraComponent, PositionComponent> &entity, std::chrono::nanoseconds) override;

		//! @brief introduciton animation when entering gameScene
		bool introAnimation(WAL::ViewEntity<CameraComponent, PositionComponent> &entity);

		//! @brief ctor
		CameraSystem(WAL::Wal &wal);
		//! @brief Default copy ctor
		CameraSystem(const CameraSystem &) = default;
		//! @brief Default dtor
		~CameraSystem() override = default;
		//! @brief A CameraManager screen system can't be assigned.
		CameraSystem &operator=(const CameraSystem &) = delete;
	};
}

		