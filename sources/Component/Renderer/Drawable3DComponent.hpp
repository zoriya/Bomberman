//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include <Models/TypeHolder.hpp>
#include "Component/Component.hpp"
#include "Drawables/ADrawable3D.hpp"
#include "Model/Model.hpp"

namespace BBM
{
	class Drawable3DComponent : public WAL::Component
	{
	public:
		//! @brief The type of the component
		std::shared_ptr<RAY::Drawables::ADrawable3D> drawable;

		//! @brief ctor
		Drawable3DComponent(WAL::Entity &entity, std::shared_ptr<RAY::Drawables::ADrawable3D> drawable)
			: WAL::Component(entity),
			  drawable(std::move(drawable))
		{}

		//! ctor
		template<typename T, typename ...Params>
		explicit Drawable3DComponent(WAL::Entity &entity, WAL::TypeHolder<T>, Params &&...params)
			: WAL::Component(entity),
			 drawable(new T(std::forward<Params>(params)...))
		{}

		//! @brief Clone a component for another or the same entity.
		//! @param entity The entity that owns the ne component.
		WAL::Component *clone(WAL::Entity &entity) const override
		{
			return new Drawable3DComponent(entity, this->drawable);
		}

		//! @brief Default copy ctor
		Drawable3DComponent(const Drawable3DComponent &) = default;
		//! @brief Default dtor
		~Drawable3DComponent() override = default;
		//! @brief Default assignment operator
		Drawable3DComponent &operator=(const Drawable3DComponent &) = delete;
	};
}