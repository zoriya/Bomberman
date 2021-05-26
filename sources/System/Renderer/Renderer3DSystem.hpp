//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include <type_traits>
#include "System/System.hpp"
#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Drawable/Drawable3DComponent.hpp"
#include "Window.hpp"

namespace BBM
{
	template <class T>
	class Renderer3DSystem : public WAL::System
	{
	private:
		//! @brief The class to render
		RAY::Window &_window;
	public:
		explicit Renderer3DSystem(RAY::Window &window)
			: WAL::System({typeid(PositionComponent), typeid(Drawable3DComponent<T>)}),
			_window(window)
		{
		}

		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime) override
		{
			auto &comp = entity.getComponent<Drawable3DComponent<T>>();
			auto &pos = entity.getComponent<PositionComponent>();

			comp.member.setPosition({pos.getX(), pos.getY(), pos.getZ()});
			comp.member.drawOn(this->_window);
		}

		Renderer3DSystem(const Renderer3DSystem &) = default;
		~Renderer3DSystem() override = default;
		Renderer3DSystem &operator=(const Renderer3DSystem &) = delete;
	};
}