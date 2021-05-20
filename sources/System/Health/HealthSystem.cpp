//
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#include "HealthSystem.hpp"

namespace BBM
{
	const std::type_info &HealthSystem::getComponent() const
	{
		return typeid(HealthComponent);
	}

	void HealthSystem::onFixedUpdate(WAL::Entity &entity)
	{
		
	}
}
