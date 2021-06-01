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

	TimerComponent::TimerComponent(WAL::Entity &entity, std::chrono::nanoseconds delay, const WAL::Callback<WAL::Entity &, const WAL::Wal &> &callback)
		: WAL::Component(entity),
		ringIn(delay),
		callback(callback)
	{}

	TimerComponent::TimerComponent(WAL::Entity &entity, std::chrono::nanoseconds delay, std::function<void(WAL::Entity &, const WAL::Wal &)> callback)
		: WAL::Component(entity),
		ringIn(delay),
		callback(std::move(callback))
	{}

	WAL::Component *TimerComponent::clone(WAL::Entity &entity) const
	{
		return new TimerComponent(entity, this->ringIn, this->callback);
	}
}