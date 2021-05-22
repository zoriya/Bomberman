/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "IRessource.hpp"
#include "Drawables/Texture.hpp"
#include "Drawables/IDrawable.hpp"
#include "Model/ModelAnimation.hpp"
#include <raylib.h>
#include <vector>

namespace RAY {
	//! @brief Basic 3D Model type
	class Model: public IRessource {
		public:

			typedef ::MaterialMapIndex MaterialType;

			//! @brief Create an model, loading a file
			//! @param filePath: path to file to load
			Model(const std::string &filePath);

			//! @brief Create an model, loading a file
			//! @param mesh: mesh to load
			Model(const Mesh &mesh);

			//! @brief A copy constructor
			Model(const Model &model) = default;

			//! @brief A model is assignable
			Model& operator=(const Model &model) = default;

			//! @brief Model destructor, unloads all related data
			~Model();

			//! @brief Load model from file (meshes and materials)
			bool load(const std::string &filePath);

			//! @brief Load model from mesh (default materials)
			bool load(const Mesh &mesh);

			//! @brief Unload model (excluding meshes) from memory (RAM and/or VRAM)
			bool unloadKeepMeshes();

			//! @brief Update model animation pose
			//! @return false if animation is not compatible
			bool setAnimation(const RAY::ModelAnimation &animation);

			//! @brief Sets a texture to the Nth material
			//! @param materielIndex The type of material to apply the texture to (serves as an index)
			//! @param texture the texture to apply
			bool setTextureToMaterial(MaterialType materialType, const RAY::Texture &texture);

			//! @brief A RAY Model is cast-able in libray's model
			operator ::Model() const;

			//! @return The number of bones in the model
			int getBoneCount() const;
		private:
			//! @brief Raw data from raylib
			::Model _model;
			
	};
};
#endif /* !Model_HPP_ */
