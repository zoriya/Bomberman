//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "Drawable2DComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	class RectangleDrawableComponent : public Drawable2DComponent
	{
	public:
		//! @brief The length of the rectangle
		unsigned int length;
		//! @brief The width of the rectangle
		unsigned int width;

		explicit RectangleDrawableComponent(WAL::Entity &entity);
		RectangleDrawableComponent(const RectangleDrawableComponent &) = default;
		~RectangleDrawableComponent() override = default;
		RectangleDrawableComponent &operator=(const RectangleDrawableComponent &) = delete;
	};
}


