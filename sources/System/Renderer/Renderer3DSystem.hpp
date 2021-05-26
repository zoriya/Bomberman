//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include <type_traits>
#include "System/System.hpp"
#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Drawable/Drawable3DComponent.hpp"
#include "Util/Utils.hpp"
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
		//! @brief ctor
		explicit Renderer3DSystem(RAY::Window &window)
			: WAL::System({typeid(PositionComponent), typeid(Drawable3DComponent<T>)}),
			_window(window)
		{
		}

		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		//! @param dtime The delta time.
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds) override
		{
			auto &comp = entity.getComponent<Drawable3DComponent<T>>();
			auto &pos = entity.getComponent<PositionComponent>();

			comp.member.setPosition(*pos.position);
			comp.member.drawOn(this->_window);
		}

		//! @brief Default copy ctor
		Renderer3DSystem(const Renderer3DSystem &) = default;
		//! @brief Default dtor
		~Renderer3DSystem() override = default;
		//! @brief Default assignment operator
		Renderer3DSystem &operator=(const Renderer3DSystem &) = delete;
	};
}