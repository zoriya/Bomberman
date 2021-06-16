//
// Created by cbihan on 16/06/2021.
//

#include "AMesh.hpp"

namespace RAY::Mesh
{
	std::shared_ptr<::Mesh> RAY::Mesh::AMesh::getRaylibMesh() const
	{
		return this->_raylibMesh;
	}
}