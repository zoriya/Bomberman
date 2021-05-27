/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Mesh
*/

#ifndef Mesh_HPP_
#define Mesh_HPP_

#include <raylib.h>
#include <string>

namespace RAY {
	//! @brief Vertex data definning a mesh
	class Mesh {
		public:
			//! @brief default constructor
			Mesh() = default;
			//! @brief Create a mesh from a raylib's mesh
			Mesh(const ::Mesh &);
			//! @brief default copy-constructor
			Mesh(const Mesh &) = default;
			//! @brief a mesh is assignable
			Mesh &operator=(const Mesh &) = default;
			//! @brief default destructor
			~Mesh() = default;

			//! @brief Export mesh to file
			//! @param file path to the file where the mesh is exported
			bool exportTo(const std::string &file);
		private:
			//! @brief Bounding box type for 3d mesh
			::Mesh _mesh;
		INTERNAL:
			operator ::Mesh() const;
	};
}
#endif /* !Mesh_HPP_ */
