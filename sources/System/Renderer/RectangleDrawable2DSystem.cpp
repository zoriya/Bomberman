//
// Created by cbihan on 24/05/2021.
//

#include "RectangleDrawable2DSystem.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Drawable/RectangleDrawable2DComponent.hpp"
#include "Window.hpp"
#include "Drawables/2D/Rectangle.hpp"

namespace BBM
{

	RectangleDrawable2DSystem::RectangleDrawable2DSystem(RAY::Window &w)
		: RendererSystem(w)
	{
	}

	void RectangleDrawable2DSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds)
	{
		auto &rectDraw = entity.getComponent<RectangleDrawableComponent>();
		auto &pos = entity.getComponent<PositionComponent>();
		RAY::Drawables::Drawables2D::Rectangle r({pos.getX(), pos.getY()},
										   {static_cast<float>(rectDraw.width), static_cast<float>(rectDraw.length)},
										   rectDraw.color);
		this->_w.draw(r);
	}
}