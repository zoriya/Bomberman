//
// Created by Louis Auzuret on 2021-05-20.
//

#pragma once

#include "Models/Callback.hpp"
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

namespace BBM 
{
	class CollisionComponent : public WAL::Component
	{
		private:
		public:
			//onCollide functions to be called
			WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollide;
			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;
			
			//! @brief A collision component with no callback.
			explicit CollisionComponent(WAL::Entity &entity);

			//! @brief Constructor with a callback function
			CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, const WAL::Entity &)> callback);

            //! @brief Constructor with a WAL::Callback
			CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> callback);

			//! @brief A default copy constructor
			CollisionComponent(const CollisionComponent &) = default;

			//! @brief default destructor
			~CollisionComponent() override = default;

			//! @brief A component can't be assigned
			CollisionComponent &operator=(const CollisionComponent &) = delete;
	};
}