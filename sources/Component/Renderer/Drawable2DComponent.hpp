//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Drawables/ADrawable2D.hpp"

namespace BBM
{
	template <class T>
	class Drawable2DComponent : public WAL::Component
	{
	public:
		//! @brief The type of the component
		T member;

		//! ctor
		Drawable2DComponent(WAL::Entity &entity, T member)
			: WAL::Component(entity),
			member(std::move(member))
		{}

		//! ctor
		template<typename ...Params>
		explicit Drawable2DComponent(WAL::Entity &entity, Params &&...params)
			: WAL::Component(entity),
			  member(std::forward<Params>(params)...)
		{}

		//! @brief Clone a component for another or the same entity.
		//! @param entity The entity that owns the ne component.
		WAL::Component *clone(WAL::Entity &entity) const override
		{
			return new Drawable2DComponent(entity, this->member);
		}

		//! @brief Default copy ctor
		Drawable2DComponent(const Drawable2DComponent &) = default;
		//! @brief Default dtor
		~Drawable2DComponent() override = default;
		//! @brief Default assignment operator
		Drawable2DComponent &operator=(const Drawable2DComponent &) = delete;


	};
}