//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include <type_traits>
#include "System/System.hpp"
#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
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
		explicit Renderer2DSystem()
			: WAL::System({typeid(PositionComponent), typeid(Drawable2DComponent<T>)}),
			_window(RAY::Window::getInstance())
		{
		}

		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		//! @param dtime The delta time.
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds) override
		{
			auto &comp = entity.getComponent<Drawable2DComponent<T>>();
			auto &pos = entity.getComponent<PositionComponent>();

			comp.member.setPosition({pos.getX(), pos.getY()});
			this->_window.draw(comp.member);
			printf("Drawing smth\n");
		}

		//! @brief default copy ctor
		Renderer2DSystem(const Renderer2DSystem &) = default;
		//! @brief default dtor
		~Renderer2DSystem() override = default;
		//! @brief Default assignment operator
		Renderer2DSystem &operator=(const Renderer2DSystem &) = delete;
	};
}