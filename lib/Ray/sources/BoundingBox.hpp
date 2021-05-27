//
// Created by Louis Auzuret on 05/27/21
//

#pragma once

#include <raylib.h>
#include "Mesh.hpp"

namespace RAY {
	//! @brief Bounding box, used in collision management
	class BoundingBox {
		public:
			//! @brief Create an boxing box, using an existant Mesh
			//! @param Mesh: mesh of the object to get bounding box from
			BoundingBox(const Mesh &mesh);
			
			//! @brief A default copy constructor
			BoundingBox(const BoundingBox &) = default;

			//! @brief A bounding box is constructible from a raylib's boundingbox
			BoundingBox(const ::BoundingBox &);

			//! @brief A circle is assignable
			BoundingBox &operator=(const BoundingBox &) = default;

			//! @return true if the boxes collide
			bool collide(const BoundingBox &other) const;
			static bool collision(const BoundingBox &box1, const BoundingBox &box2);

			//! @brief A default destructor
			~BoundingBox() = default;

		private:
			//! @brief Bounding box type for 3d mesh
			::BoundingBox _boundingBox;
		INTERNAL:
			operator ::BoundingBox() const;
	};
}