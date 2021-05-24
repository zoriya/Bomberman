//
// Created by cbihan on 24/05/2021.
//

#include "Drawable2DComponent.hpp"
#include "Component/Component.hpp"

namespace BBM
{
	Drawable2DComponent::Drawable2DComponent(WAL::Entity &entity)
		: WAL::Component(entity),
		  color(0)
	{
	}
}