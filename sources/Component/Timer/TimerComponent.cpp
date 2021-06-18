//
// Created by Zoe Roux on 5/31/21.
//

#include "TimerComponent.hpp"

#include <utility>

namespace BBM
{
	TimerComponent::TimerComponent(WAL::Entity &entity, std::chrono::nanoseconds delay)
		: WAL::Component(entity),
		ringIn(delay)
	{}

	TimerComponent::TimerComponent(WAL::Entity &entity, std::chrono::nanoseconds delay, const WAL::Callback<WAL::Entity &, WAL::Wal &> &timerCallback)
		: WAL::Component(entity),
		callback(timerCallback),
		ringIn(delay)
	{}

	WAL::Component *TimerComponent::clone(WAL::Entity &entity) const
	{
		return new TimerComponent(entity, this->ringIn, this->callback);
	}
}