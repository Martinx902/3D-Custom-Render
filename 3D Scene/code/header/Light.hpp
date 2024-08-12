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
	 * @brief Represents a light source in the scene.
	 */
	class Light : public Node
	{
		float intensity;		 ///< The diffuse intensity of the light, based on the Fong model.
		float ambient_intensity; ///< The minimum intensity a color is going to get if their normals dont face the light.

	public:

		/**
		 * @brief Creates a light source in the scene and sets its parameters
		 *
		 * @param given_scene Pointer to the parent scene.
		 * @param given_intensity The intensity of the light.
		 * @param given_ambient_light The ambient intensity of the light (default is 0.2f).
		 */
		Light(Scene* given_scene, float given_intensity, float given_ambient_light = 0.2f)
			:
			intensity(given_intensity),
			ambient_intensity(given_ambient_light),
			Node(given_scene)
		{}

		/**
		 * @brief Moves the light up and down in a ping-pong movement, just for debug/visual purpouses.
		 */
		void update() override;

		/**
		 * @brief Applies a view transform to the light.
		 *
		 * @param view_matrix The view matrix to apply.
		 */
		void apply_view_transform(const Matrix44& view_matrix);

		/**
		 * @brief Calculates the intensity of the light at a given point with a given normal based on the Lambert model, using the dot product between the position and the normal vector
		 *
		 * @param point The point at which to calculate the light intensity.
		 * @param normal The normal vector at the point.
		 * @return The final light intensity the normal of the vertex is going to receive.
		 */
		float calculate_light_intensity(const Vector3f& point, const Vector3f& normal);
	};
}