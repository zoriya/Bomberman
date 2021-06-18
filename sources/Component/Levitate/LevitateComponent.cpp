//
// Created by hbenjamin on 07/06/2021.
//

#include "LevitateComponent.hpp"

namespace BBM
{
	LevitateComponent::LevitateComponent(WAL::Entity &entity)
			: WAL::Component(entity),
			  y()
	{}

	LevitateComponent::LevitateComponent(WAL::Entity &entity, float entityY)
			: WAL::Component(entity),
			  y(entityY)
	{}

	WAL::Component *LevitateComponent::clone(WAL::Entity &entity) const
	{
		return new LevitateComponent(entity);
	}

} // namespace BMM