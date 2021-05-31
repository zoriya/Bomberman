//
// Created by Louis Auzuret on 2021-05-20.
//

#pragma once

#include "Models/Callback.hpp"
#include "Models/Vector3.hpp"
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

namespace BBM 
{
	class CollisionComponent : public WAL::Component
	{
		private:
			Vector3f _bound;
		public:
			//! @brief get bound size on the X axis
			float getBoundX(void) const;
			//! @brief get bound size on the Y axis
			float getBoundY(void) const;
			//! @brief get bound size on the Z axis
			float getBoundZ(void) const;
			//! @brief set bound size on the X axis
			void setBoundX(float);
			//! @brief set bound size on the Y axis
			void setBoundY(float);
			//! @brief set bound size on the Z axis
			void setBoundZ(float);
			//onCollide functions to be called
			WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollide;
			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;
			
			//! @brief A component can't be instantiated, it should be derived.
			explicit CollisionComponent(WAL::Entity &entity);

			//! @brief Constructor with a callback function
			CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, const WAL::Entity &)> callback, Vector3f bound);

			//! @brief Constructor with a callback function
			CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, const WAL::Entity &)> callback, float boundSize = 0);

			//! @brief Constructor with a WAL::Callback
			CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> callback, Vector3f bound);

			//! @brief Constructor with a WAL::Callback
			CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> callback, float boundSize = 0);

			//! @brief Constructor of collider with no callback
			CollisionComponent(WAL::Entity &entity, Vector3f bound);

			//! @brief Constructor no callback, same boundSize for all axis
			CollisionComponent(WAL::Entity &entity, float boundSize);

			//! @brief A component can't be instantiated, it should be derived.
			CollisionComponent(const CollisionComponent &) = default;

			//! @brief default destructor
			~CollisionComponent() override = default;

			//! @brief A component can't be assigned
			CollisionComponent &operator=(const CollisionComponent &) = delete;
	};
}