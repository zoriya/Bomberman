//
// Created by Louis Auzuret on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/Component/Component.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace BBM 
{
	class CollisionComponent : public WAL::Component
	{

		private:
			int _boundX;
            int _boundY;
            int _boundZ;
		public:

			//! @brief get bound size on the X axis
            int getBoundX(void) const;
			//! @brief get bound size on the Y axis
			int getBoundY(void) const;
			//! @brief get bound size on the Z axis
            int getBoundZ(void) const;
			//! @brief set bound size on the X axis
            void setBoundX(int);
			//! @brief set bound size on the Y axis
			void setBoundY(int);
			//! @brief set bound size on the Z axis
            void setBoundZ(int);
			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;
			
			//! @brief A component can't be instantiated, it should be derived.
			explicit CollisionComponent(WAL::Entity &entity);

			//! @brief Constructor for cube hitbox
			CollisionComponent(WAL::Entity &entity, int boundSize);

            //! @brief Constructor
			CollisionComponent(WAL::Entity &entity, int boundX, int boundY, int boundZ);

			//! @brief A component can't be instantiated, it should be derived.
			CollisionComponent(const CollisionComponent &) = default;

			//! @brief default destructor
			~CollisionComponent() override = default;

			//! @brief A component can't be assigned
			CollisionComponent &operator=(const CollisionComponent &) = delete;
	};
}