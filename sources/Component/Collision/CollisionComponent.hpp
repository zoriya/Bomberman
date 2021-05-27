//
// Created by Louis Auzuret on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/Models/Callback.hpp"
#include "lib/wal/sources/Component/Component.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace BBM 
{
	class CollisionComponent : public WAL::Component
	{
		private:
			WAL::Callback<WAL::Entity &, WAL::Entity &> onCollide;
		public:
			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;
			
			//! @brief A collision component with no callback.
			explicit CollisionComponent(WAL::Entity &entity);

			//! @brief Constructor with a callback function
			CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, WAL::Entity &)> callback);

            //! @brief Constructor with a WAL::Callback
			CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, WAL::Entity &> callback);

			//! @brief A default copy constructor
			CollisionComponent(const CollisionComponent &) = default;

			//! @brief default destructor
			~CollisionComponent() override = default;

			//! @brief A component can't be assigned
			CollisionComponent &operator=(const CollisionComponent &) = delete;
	};
}