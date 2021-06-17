//
// Created by cbihan on 16/06/2021.
//

#include "MeshSphere.hpp"

namespace RAY::Mesh
{
	MeshSphere::MeshSphere(float radius_arg, int rings_arg, int slices_arg) :
		radius(radius_arg),
		rings(rings_arg),
		slices(slices_arg)
	{
		this->_raylibMesh = std::make_shared<::Mesh>(GenMeshSphere(radius_arg, rings_arg, slices_arg));
	}
}