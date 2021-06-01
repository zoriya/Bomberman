/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "Drawables/Texture.hpp"
#include "Drawables/ADrawable3D.hpp"
#include "Model/ModelAnimation.hpp"
#include <raylib.h>
#include <vector>
#include <optional>
#include <unordered_map>
#include <memory>

namespace RAY::Drawables::Drawables3D {
	//! @brief Basic 3D Model type
	class Model: public Drawables::ADrawable3D {
		public:

			typedef ::MaterialMapIndex MaterialType;

			//! @brief Create an model, loading a file
			//! @param filePath: path to file to load
			Model(const std::string &filePath,
			      std::optional<std::pair<MaterialType, std::string>> texture = std::nullopt,
			      const RAY::Vector3 &position = {0, 0, 0},
			      const RAY::Vector3 &rotationAxis = RAY::Vector3(0, 1, 0),
			      float rotationAngle = 0,
			      const RAY::Vector3 &scale = RAY::Vector3(1, 1, 1));

			//! @brief Create an model, loading a file
			//! @param mesh: mesh to load
			Model(const Mesh &mesh);

			//! @brief A copy constructor
			Model(const Model &model) = default;

			//! @brief A model is assignable
			Model& operator=(const Model &model) = default;

			//! @brief Model destructor, model's data will be deleted if it's the last entity alive
			~Model() override = default;

			//! @brief Unload model (excluding meshes) from memory (RAM and/or VRAM)
			bool unloadKeepMeshes();

			//! @brief Update model animation pose
			bool setAnimation(const RAY::ModelAnimation &animation);

			//! @brief Sets a texture to the Nth material
			//! @param materielIndex The type of material to apply the texture to (serves as an index)
			//! @param texture the texture to apply
			bool setTextureToMaterial(MaterialType materialType, const std::string &texture);

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

			void drawOn(RAY::Window &) override;

		private:
			//! @brief Raw data from raylib
			std::shared_ptr<::Model> _model;
			//! @brief The list of textures that can be applied to this model.
			std::unordered_map<MaterialType, Texture> _textureList;
			//! @brief Rotation property
			RAY::Vector3 _rotationAxis;
			//! @brief Rotation property
			float _rotationAngle;
			//! @brief Scale of the shape
			RAY::Vector3 _scale;
			//! @brief, look through cache to see if a model using same file
			std::shared_ptr<::Model>fetchModelInCache(const std::string &path);

			static std::unordered_map<std::string, std::shared_ptr<::Model>> _modelsCache;

		INTERNAL:
			//! @brief A RAY Model is cast-able in libray's model
			operator ::Model() const;
			
	};
};
#endif /* !Model_HPP_ */
