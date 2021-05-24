//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Drawables/ADrawable2D.hpp"
#include "Color.hpp"

namespace BBM
{
	class Drawable2DComponent : public WAL::Component
	{
	public:
		//! @brief color of the drawable
		RAY::Color color;
		//! @brief The rotation (clock wise)
		int rotation;

		explicit Drawable2DComponent(WAL::Entity &entity);
	};
}