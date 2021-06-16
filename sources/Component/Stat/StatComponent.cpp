//
//
//

#include "StatComponent.hpp"

namespace BBM
{

	StatComponent::StatComponent(WAL::Entity &entity, WAL::Callback<Drawable2DComponent &> callback)
		: Component(entity),
		updater(callback)
	{}

	WAL::Component *StatComponent::clone(WAL::Entity &entity) const
	{
		return new StatComponent(entity, this->updater);
	}
} // namespace WAL