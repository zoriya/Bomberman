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
#include <iostream>

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
		virtual void onUpdate(ViewEntity<Dependencies...> &entity, std::chrono::nanoseconds dtime) {}

		//! @brief An alternative of onUpdate that is called every 8ms (120 times per seconds). If the system slow down, it will try to catch up.
		//! @remark This should be used for Physics, AI and everything that could be imprecise due to float rounding.
		//! @param entity The entity to update.
		virtual void onFixedUpdate(ViewEntity<Dependencies...> &entity) {}

		//! @brief A method called after all entities that this system manage has been updated.
		virtual void onSelfUpdate() {}


		//! @brief Update the whole system (every entities that this system is responsible can be updated.
		//! @param dtime The delta time since the last call to this method.
		void update(std::chrono::nanoseconds dtime) final
		{
			for (auto &entity : this->getView())
				this->onUpdate(entity, dtime);
			this->onSelfUpdate();
		}

		//! @brief An alternative of update that is called every 8ms (120 times per seconds). If the system slow down, it will try to catch up.
		//! @remark This should be used for Physics, AI and everything that could be imprecise due to float rounding.
		void fixedUpdate() final
		{
			for (auto &entity : this->getView())
				this->onFixedUpdate(entity);
		}
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