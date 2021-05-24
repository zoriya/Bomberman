//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Drawables/ADrawable2D.hpp"
#include "Color.hpp"

namespace BBM
{
	template <class T>
	class DrawableComponent : public WAL::Component
	{
	public:
		T member;

		explicit DrawableComponent(WAL::Entity &entity)
			: WAL::Component(entity)
		{
		}
	};
}