/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#pragma once

#include "Node.hpp"

namespace MScenary
{
	/**
	 * @brief Class representing the main camera of the scene, it allows for movement and input receiving
	 */
	class Camera : public Node
	{
		Matrix44 perspective_matrix; ///< The projection matrix for the scene view_matrix * this = projection_matrix.

		float movement_speed; ///< The speed of movement for the camera.
		float rotation_speed; ///< The speed of rotation for the camera.

	public:

		/**
		 * @brief Creates a camera object with a defined fov, near plane, far plane and some inputs variables, also initializes the projection matrix.
		 *
		 * @param given_scene Pointer to the parent scene.
		 * @param fov The field of view angle.
		 * @param near_d The near plane distance.
		 * @param far_d The far plane distance.
		 * @param movement_speed The speed of movement for the camera.
		 * @param given_rotation_speed The speed of rotation for the camera.
		 */
		Camera(Scene* given_scene, float fov, float near_d, float far_d, float movement_speed, float given_rotation_speed);

		/**
		 * @brief Gets the input of the camera and moves/rotates around the scene
		 */
		void update() override;

		/**
		 * @brief Handles rotation input for the camera.
		 *
		 * @param rot_x The rotation around the x-axis.
		 * @param rot_y The rotation around the y-axis.
		 */
		void rotation_input(float& rot_x, float& rot_y);

		/**
		 * @brief Handles movement panning/zoom input for the camera.
		 *
		 * @param pos_y The position change along the y-axis.
		 * @param pos_x The position change along the x-axis.
		 * @param pos_z The position change along the z-axis.
		 */
		void movement_input(float& pos_y, float& pos_x, float& pos_z);

		/**
		 * @brief Multiplies the view_matrix * perspective matrix to set the projection matrix and send it as one already combined
		 *
		 * @return The projection matrix.
		 */
		Matrix44 get_projection_matrix();

		/**
		 * @brief Gets the inverse of the trasnform of the camera matrix
		 *
		 * @return The view matrix.
		 */
		Matrix44 get_view_matrix();
	};
}