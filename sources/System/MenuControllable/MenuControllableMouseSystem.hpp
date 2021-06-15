//
// Created by Louis Auzuret on 06/03/21
//

#pragma once

#include "Component/Controllable/ControllableComponent.hpp"
#include "Models/Vector2.hpp"
#include "System/System.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"

namespace BBM
{
	//! @brief A system to handle Controllable entities in a menu.
	class MenuControllableMouseSystem : public WAL::System<ControllableComponent, PositionComponent, Drawable2DComponent>
	{
	private:
		//! @brief index of the current button selected
		WAL::Entity *_currentButton;
	public:
		//! @brief time (in millisecond) since last check
		std::chrono::time_point<std::chrono::steady_clock> now;
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<ControllableComponent, PositionComponent, Drawable2DComponent> &entities) override;

		//! @brief A default constructor
		explicit MenuControllableMouseSystem(WAL::Wal &wal);
		//! @brief A MenuControllable system is not copy constructable
		MenuControllableMouseSystem(const MenuControllableMouseSystem &) = delete;
		//! @brief A default destructor
		~MenuControllableMouseSystem() override = default;
		//! @brief A MenuControllable system is not assignable.
		MenuControllableMouseSystem &operator=(const MenuControllableMouseSystem &) = delete;
	};
}
