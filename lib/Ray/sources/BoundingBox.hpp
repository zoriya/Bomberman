//
// Created by Louis Auzuret on 05/27/21
//

#pragma once

#include <raylib.h>
#include "Mesh.hpp"
#include "Vector/Vector3.hpp" 

namespace RAY {
	//! @brief Bounding box, used in collision management
	class BoundingBox {
		public:
			//! @brief Create an default boxing box, no values are init
			BoundingBox() = default;
			//! @brief Create an boxing box, using an existant Mesh
			//! @param Mesh: mesh of the object to get bounding box from
			BoundingBox(const Mesh &mesh);

			//! @brief Create an boxing box, using vertex data
			//! @param min Minimum vertex box-corner
			//! @param max Maximum vertex box-corner
			BoundingBox(const Vector3 &min, const Vector3 &max);
			
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

			//! @return Minimum vertex box-corner
			RAY::Vector3 getMin() const;
			//! @return Maximum vertex box-corner
			RAY::Vector3 getMax() const;
			//! @param min Minimum vertex box-corner
			void setMin(const RAY::Vector3 &min);
			//! @param max Maximum vertex box-corner
			void setMax(const RAY::Vector3 &max);

		private:
			//! @brief Bounding box type for 3d mesh
			::BoundingBox _boundingBox;
		INTERNAL:
			operator ::BoundingBox() const;
	};
}