//
// Created by Utilisateur on 08/06/2021.
//

#include "BasicBombComponent.hpp"

namespace BBM
{
	BasicBombComponent::BasicBombComponent(WAL::Entity &entity, int damage, float explosionRadius)
			: WAL::Component(entity),
			damage(damage),
			explosionRadius(explosionRadius)
	{}

	WAL::Component *BasicBombComponent::clone(WAL::Entity &entity) const
	{
		return new BasicBombComponent(entity, this->damage, this->explosionRadius);
	}
}