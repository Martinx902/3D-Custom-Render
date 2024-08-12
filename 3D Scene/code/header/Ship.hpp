/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#pragma once

#include "Model.hpp"

namespace MScenary
{
	/**
	 * @brief Represents a ship model in the center of the island in the scene.
	 *
	 * This class extends the Model class and provides functionality specific to a ship.
	 */
	class Ship : public Model
	{
		float ping_pong_movement; ///< Movement value for ping-pong motion.
		float movement_speed;     ///< Speed of movement for position and rotation.

	public:

		/**
		 * @brief Constructs a new Ship object with its local variables and the ones inherited from model
		 *
		 * @param given_scene     Pointer to the scene.
		 * @param mesh_file_path  Path to the mesh file.
		 * @param given_movement  Movement value for ping-pong motion.
		 * @param given_speed     Speed of movement.
		 */
		Ship(Scene* given_scene, const char* mesh_file_path, float given_movement, float given_speed)
			: ping_pong_movement(given_movement), movement_speed(given_speed), Model(given_scene, mesh_file_path)
		{
			initialize_model(mesh_file_path);
		}

		/**
		 * @brief Moves the ship up and down as well as rotates it.
		 */
		void update() override;
	};
}