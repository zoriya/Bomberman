
#include "ScoreComponent.hpp"

namespace BBM
{
	ScoreComponent::ScoreComponent(WAL::Entity &entity)
		: Component(entity),
		  score(PLAYING)
	{}

	WAL::Component *ScoreComponent::clone(WAL::Entity &entity) const
	{
		return new ScoreComponent(entity);
	}

} // namespace WAL