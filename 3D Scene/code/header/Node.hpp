/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#pragma once

#include "Transform.hpp"

namespace MScenary
{
	class Scene;
	class Light;

	/**
	 * @brief Base class representing a node in a scene hierarchy.
	 *
	 * This class provides common functionality and properties for nodes in a scene so it can created a scene graph to use hierarchy.
	 */
	class Node
	{
	protected:

		Scene* scene;		  ///< Pointer to the scene containing the node.
		Transform* transform; ///< Pointer to the transform of the node that stores the transform matrix.

	public:

		/**
		 * @brief Constructs a Node object.
		 *
		 * @param given_scene Pointer to the scene where the node belongs.
		 */
		Node(Scene* given_scene) : transform(new Transform()), scene(given_scene) {}

		/**
		 * @brief Updates the node. It should be used to move the nodes around the scene and some physics/movement calculations.
		 */
		virtual void update() {}

		/**
		 * @brief Renders the node and passes along a serie of useful matrices for its render calculations.
		 *
		 * @param projection_matrix The projection matrix for rendering.
		 * @param view_matrix The view matrix for rendering.
		 * @param light_source The light source for rendering.
		 */
		virtual void render(const Matrix44& projection_matrix, const Matrix44& view_matrix, Light& light_source) {}

		/**
		 * @brief Gets the transform of the node.
		 *
		 * @return Pointer to the transform.
		 */
		Transform* get_transform()
		{
			return transform;
		}
	};
}