/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "IRessource.hpp"
#include <raylib.h>

namespace RAY {
    //! @brief Basic 3d Model type
    class Model: public IRessource {
        public:
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

            ~Model();

            //! @brief Load model from file (meshes and materials)
            bool load(const std::string &filePath);

            //! @brief Load model from mesh (default materials)
            bool load(const Mesh &mesh);

            //! @brief Unload model (including meshes) from memory (RAM and/or VRAM)
            bool unload();

            //! @brief Unload model (excluding meshes) from memory (RAM and/or VRAM)
            bool unloadKeepMeshes();
        private:
            ::Model _model;
    };
};
#endif /* !Model_HPP_ */
