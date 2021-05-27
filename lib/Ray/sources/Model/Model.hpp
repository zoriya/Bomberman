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
#include "Drawables/ADrawable3D.hpp"
#include "Model/ModelAnimation.hpp"
#include <raylib.h>
#include <vector>

namespace RAY::Drawables::Drawables3D {
	//! @brief Basic 3D Model type
	class Model: public IRessource, public Drawables::ADrawable3D {
		public:

			typedef ::MaterialMapIndex MaterialType;

			//! @brief Create an model, loading a file
			//! @param filePath: path to file to load
			Model(const std::string &filePath, const RAY::Vector3 &position = {0, 0, 0}, const RAY::Vector3 &rotationAxis = RAY::Vector3(0, 1, 0), float rotationAngle = 0, const RAY::Vector3 &scale = RAY::Vector3(1, 1, 1));

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

			//! @brief Unload model (including meshes) from memory (RAM and/or VRAM)
			bool unload() override;

			//! @brief Unload model (excluding meshes) from memory (RAM and/or VRAM)
			bool unloadKeepMeshes();

			//! @brief Update model animation pose
			bool setAnimation(const RAY::ModelAnimation &animation);

			//! @brief Sets a texture to the Nth material
			//! @param materielIndex The type of material to apply the texture to (serves as an index)
			//! @param texture the texture to apply
			bool setTextureToMaterial(MaterialType materialType, const RAY::Texture &texture);

			//! @return The number of bones in the model
			int getBoneCount() const;

			//! @brief Set rotation angle
			Model &setRotationAngle(float roationAngle);

			//! @return rotation angle
			float getRotationAngle(void);
	
			//! @brief Set Rotation Axis
			Model &setRotationAxis(const RAY::Vector3 &scale);

			//! @return rotation axis
			const RAY::Vector3 & getRotationAxis(void);

			//! @brief Set Scale
			Model &setScale(const RAY::Vector3 &scale);

			//! @return Scale
			const RAY::Vector3 & getScale(void);

			//! @brief Draw Model on window
			void drawOn(RAY::Window &) override;

			//! @brief Get bounding box
			RAY::BoundingBox getBoundingBox(void) override;
		private:
			//! @brief Raw data from raylib
			::Model _model;
			//! @brief Rotation property
			RAY::Vector3 _rotationAxis;
			//! @brief Rotation property
			float _rotationAngle;
			//! @brief Scale of the shape
			RAY::Vector3 _scale;

		INTERNAL:
			//! @brief A RAY Model is cast-able in libray's model
			operator ::Model() const;
			
	};
};
#endif /* !Model_HPP_ */
