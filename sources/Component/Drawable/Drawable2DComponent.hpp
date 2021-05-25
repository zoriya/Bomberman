//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Drawables/ADrawable2D.hpp"

namespace BBM
{
	template <class T>
	class Drawable2DComponent : public WAL::Component, public T
	{
	public:

		explicit Drawable2DComponent(WAL::Entity &entity)
			: WAL::Component(entity)
		{
		}

		WAL::Component *clone(WAL::Entity &entity) const override
		{
			return new Drawable2DComponent(entity);
		}


	};
}