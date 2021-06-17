//
// Created by cbihan on 16/06/2021.
//

#pragma once

#include <raylib.h>
#include "AMesh.hpp"
#include <memory>

namespace RAY::Mesh
{
	class MeshSphere : public AMesh
	{
	public:
		//! @brief radius
		float radius;
		//! @brief rings
		int rings;
		//! @brief slices
		int slices;


		//! @brief ctor
		MeshSphere(float radius_arg, int rings_arg, int slices_arg);
		//! @brief copy ctor
		MeshSphere(const MeshSphere &) = default;
		//! @brief dtor
		~MeshSphere() = default;
		//! @brief assignment operator
		MeshSphere &operator=(const MeshSphere &) = default;

	};

}
