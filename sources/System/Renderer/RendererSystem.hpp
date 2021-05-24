//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include <type_traits>
#include "System/System.hpp"
#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Drawable/DrawableComponent.hpp"
#include "Window.hpp"

namespace BBM
{
	template <class T>
	class RendererSystem : public WAL::System
	{
	private:
		//! @brief The class to render
		RAY::Window &_window;
	public:
		explicit RendererSystem(RAY::Window &window)
			: WAL::System({typeid(PositionComponent), typeid(DrawableComponent<T>)}),
			_window(window)
		{
		}

		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime) override
		{
			auto &comp = entity.getComponent<DrawableComponent<T>>();
			auto &pos = entity.getComponent<PositionComponent>();

			// TODO update drawable pos with pos
			comp.member.drawOn(this->_window);
		}

		RendererSystem(const RendererSystem &) = default;
		~RendererSystem() override = default;
		RendererSystem &operator=(const RendererSystem &) = delete;
	};
}