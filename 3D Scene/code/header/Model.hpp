/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#pragma once

#include "Node.hpp"
#include "Mesh.hpp"

#include <memory>
#include <vector>

namespace MScenary
{
	class Scene;
	class Light;

	/**
	 * @brief Represents a model consisting of multiple meshes.
	 */
	class Model : public Node
	{
		std::vector<std::shared_ptr<Mesh>> meshes; ///< Vector of meshes that make up the model.

	public:

		/**
		 * @brief Constructs a Model object by importing an asset from memory and creating as many meshes as the model has.
		 *
		 * @param given_scene Pointer to the scene where the model is placed.
		 * @param mesh_file_path The file path of the mesh data.
		 */
		Model(Scene* given_scene, const char* mesh_file_path);

		/**
		 * @brief Passes along the meshes the projection and view matrix multiplied by the model coordinates already.
		 *
		 * @param projection_matrix The projection matrix.
		 * @param view_matrix The view matrix.
		 * @param light_source The light source for illumination.
		 */
		void render(const Matrix44& projection_matrix, const Matrix44& view_matrix, Light& light_source) override;

	protected:

		/**
		 * @brief Initializes the model by loading mesh data from a file using Assimp.
		 *
		 * @param mesh_file_path The file path of the mesh data.
		 */
		void initialize_model(const char* mesh_file_path);
	};
}