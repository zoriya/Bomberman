//
// Created by Zoe Roux on 2021-05-14.
//

#pragma once

#include <chrono>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include "Entity/Entity.hpp"
#include "Wal.hpp"
#include "View/View.hpp"
#include "ISystem.hpp"

namespace WAL
{
	//! @brief A base system of WAL
	//! @tparam Dependencies The list of dependencies this system has.
	template<typename ...Dependencies>
	class System : public ISystem
	{
	public:
		//! @brief A virtual, default, destructor
		~System() override = default;
		//! @brief A system can be moved
		System(System &&) noexcept = default;

		//! @brief Get a view of all entities containing every dependencies of this system.
		View<Dependencies...> &getView() override
		{
			return this->_wal.scene->template view<Dependencies...>();
		}

		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		//! @param dtime The delta time.
		void onUpdate(Entity &entity, std::chrono::nanoseconds dtime) override {}

		//! @brief An alternative of onUpdate that is called every 8ms (120 times per seconds). If the system slow down, it will try to catch up.
		//! @remark This should be used for Physics, AI and everything that could be imprecise due to float rounding.
		//! @param entity The entity to update.
		void onFixedUpdate(Entity &entity) override {}

		//! @brief A method called after all entities that this system manage has been updated.
		void onSelfUpdate() override {}
	protected:
		//! @brief A reference to the ECS.
		Wal &_wal;

		//! @brief A system can't be instantiated, it should be derived.
		explicit System(Wal &wal)
			: _wal(wal)
		{}
		//! @brief A system can't be instantiated, it should be derived.
		System(const System &) = default;
		//! @brief A system can't be instantiated, it should be derived.
		System &operator=(const System &) = default;
	};
} // namespace WAL