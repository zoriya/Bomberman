//
// Created by Zoe Roux on 5/27/21.
//

#include "CameraComponent.hpp"

namespace BBM
{
	CameraComponent::CameraComponent(WAL::Entity &entity)
		: Component(entity)
	{}

	WAL::Component *BBM::CameraComponent::clone(WAL::Entity &entity) const
	{
		return new CameraComponent(entity);
	}
}