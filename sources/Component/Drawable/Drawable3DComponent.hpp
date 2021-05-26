//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Drawables/ADrawable3D.hpp"

namespace BBM
{
	template <class T>
	class Drawable3DComponent : public WAL::Component
	{
	public:
		T member;

		explicit Drawable3DComponent(WAL::Entity &entity, T member)
			: WAL::Component(entity),
			member(std::move(member))
		{
		}

		WAL::Component *clone(WAL::Entity &entity) const override
		{
			return new Drawable3DComponent(entity, this->member);
		}
	};
}