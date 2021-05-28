//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Drawables/IDrawable.hpp"
#include "Drawables/ADrawable3D.hpp"

namespace BBM
{
	class Drawable3DComponent : public WAL::Component
	{
	public:
		//! @brief The type of the component
		std::shared_ptr<RAY::Drawables::ADrawable3D> &member;

		//! @brief ctor
		template <class T>
		explicit Drawable3DComponent(WAL::Entity &entity, std::shared_ptr<T> member)
			: WAL::Component(entity),
			member(member)
		{
		}

		//! @brief Clone a component for another or the same entity.
		//! @param entity The entity that owns the ne component.
		WAL::Component *clone(WAL::Entity &entity) const override
		{
			return new Drawable3DComponent(entity, this->member);
		}

		//! @brief Default copy ctor
		Drawable3DComponent(const Drawable3DComponent &) = default;
		//! @brief Default dtor
		~Drawable3DComponent() override = default;
		//! @brief Default assignment operator
		Drawable3DComponent &operator=(const Drawable3DComponent &) = delete;
	};
}