//
//
//

#include "ColorComponent.hpp"

namespace BBM
{

	ColorComponent::ColorComponent(WAL::Entity &entity, RAY::Color componentColor)
		: Component(entity),
		  color(componentColor)
	{}

	ColorComponent::ColorComponent(WAL::Entity &entity, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
		: Component(entity),
		  color(r, g, b, a)
	{}

	WAL::Component *ColorComponent::clone(WAL::Entity &entity) const
	{
		return new ColorComponent(entity, this->color);
	}
} // namespace WAL