//
// Created by cbihan on 16/06/2021.
//

#pragma once

#include <raylib.h>
#include <memory>

namespace RAY::Mesh
{
	class AMesh
	{
	protected:
		std::shared_ptr<::Mesh> _raylibMesh;

	INTERNAL:
		//! @brief getter for _raylibMesh
		std::shared_ptr<::Mesh> getRaylibMesh() const;

	public:

		//! @brief dtor
		virtual ~AMesh() = default;

	};

}