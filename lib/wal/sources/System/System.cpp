//
// Created by Zoe Roux on 5/17/21.
//

#include "System.hpp"

#include <utility>

namespace WAL
{
	System::System(std::vector<std::type_index> dependencies)
		: _dependencies(std::move(dependencies))
	{}

	void System::onUpdate(Entity &entity, std::chrono::nanoseconds dtime)
	{}

	void System::onFixedUpdate(Entity &entity)
	{}

	void System::onSelfUpdate()
	{}

	const std::vector<std::type_index> &System::getDependencies() const
	{
		return this->_dependencies;
	}
} // namespace WAL