
#include "ScoreComponent.hpp"

namespace BBM
{
	ScoreComponent::ScoreComponent(WAL::Entity &entity)
		: Component(entity),
		  aliveTime(std::chrono::nanoseconds::zero())
	{}

	WAL::Component *ScoreComponent::clone(WAL::Entity &entity) const
	{
		return new ScoreComponent(entity);
	}

} // namespace WAL