//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include <type_traits>
#include "System/System.hpp"
#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Drawable/Drawable2DComponent.hpp"
#include "Window.hpp"

namespace BBM
{
	template <class T>
	class Renderer2DSystem : public WAL::System
	{
	private:
		//! @brief The class to render
		RAY::Window &_window;
	public:
		explicit Renderer2DSystem(RAY::Window &window)
			: WAL::System({typeid(PositionComponent), typeid(Drawable2DComponent<T>)}),
			_window(window)
		{
		}

		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		//! @param dtime The delta time.
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime) override
		{
			auto &comp = entity.getComponent<Drawable2DComponent<T>>();
			auto &pos = entity.getComponent<PositionComponent>();

			comp.member.setPosition({pos.getX(), pos.getY()});
			comp.member.drawOn(this->_window);
		}

		//! @brief default copy ctor
		Renderer2DSystem(const Renderer2DSystem &) = default;
		//! @brief default dtor
		~Renderer2DSystem() override = default;
		//! @brief Default assignment operator
		Renderer2DSystem &operator=(const Renderer2DSystem &) = delete;
	};
}