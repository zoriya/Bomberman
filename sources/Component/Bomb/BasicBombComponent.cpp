//
// Created by Utilisateur on 08/06/2021.
//

#include "BasicBombComponent.hpp"

#include <utility>

namespace BBM
{
	BasicBombComponent::BasicBombComponent(WAL::Entity &entity, int damageHit, int radius, std::vector<unsigned> ignored)
		: WAL::Component(entity),
		explosionRadius(radius),
		damage(damageHit),
		ignoredEntities(std::move(ignored))
	{}

	WAL::Component *BasicBombComponent::clone(WAL::Entity &entity) const
	{
		return new BasicBombComponent(entity, this->damage, this->explosionRadius, this->ignoredEntities);
	}
}