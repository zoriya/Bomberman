//
//
//

#include "ColorComponent.hpp"

namespace BBM
{

	ColorComponent::ColorComponent(WAL::Entity &entity, RAY::Color color)
		: Component(entity),
		  color(color)
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