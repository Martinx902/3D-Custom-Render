/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "math.hpp"

using namespace std;

namespace MScenary
{
	/**
	 * @brief Class representing transformation properties and behaviour of a node on scene.
	 */
	class Transform
	{
		Transform* transform_parent;	///< Pointer to the parent transformation component

		Vector3f Position;				///< Position vector
		Vector3f Scale;					///< Scale vector
		Vector3f Rotation;				///< Euler rotation angles

	public:

		/**
		 * @brief Constructor for the transform component.
		 * @param entity Pointer to the entity this component belongs to.
		 */
		Transform() :
			Position(Vector3f(0, 0, 0)),
			Scale(Vector3f(1, 1, 1)),
			Rotation(Vector3f(0, 0, 0)),
			transform_parent(nullptr)
		{}

		void set_transform_parent(Transform* new_parent)
		{
			transform_parent = new_parent;
		}

		/**
		 * @brief Calculates the transformation matrix based on position, rotation, and scale. Uses OpenGLToolkit for calculations.
		 * @return Transformation matrix.
		 */
		Matrix44 get_transform_matrix();

		/**
		 * @brief Gets the pointer to the parent transformation component.
		 * @return Pointer to the parent transformation component.
		 */
		Transform* get_transform_parent()
		{
			return transform_parent;
		}

		/**
		 * @brief Gets the pointer to the parent transformation component (const version).
		 * @return Pointer to the parent transformation component.
		 */
		const Transform* get_transform_parent() const
		{
			return transform_parent;
		}

		Vector3f get_position()
		{
			return Position;
		}

		const Vector3f get_position() const
		{
			return Position;
		}

        Vector3f get_rotation()
        {
            return Rotation;
        }

        const Vector3f get_rotation() const
        {
            return Rotation;
        }

		void set_position(float x, float y, float z)
		{
			Position = Vector3f(x, y, z);
		}

		void set_position_z(float z)
		{
			Position.z = z;
		}

		void set_rotation(float x, float y, float z)
		{
			Rotation = Vector3f(x, y, z);
		}

		void set_scale(float x, float y, float z)
		{
			Scale = Vector3f(x, y, z);
		}

		void set_scale(float scale)
		{
			Scale *= scale;
		}
	};
}