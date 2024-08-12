/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include <cmath>

#include "../header/Transform.hpp"
#include "../header/math.hpp"

namespace MScenary
{
	Matrix44 Transform::get_transform_matrix()
	{
		Matrix44 matrix(1);

		//M' = T * R * S

		matrix = translate(matrix, Position);
		matrix = scale(matrix, Scale);
		matrix = rotate(matrix, Rotation.x, Vector3f(1, 0, 0));
		matrix = rotate(matrix, Rotation.y, Vector3f(0, 1, 0));
		matrix = rotate(matrix, Rotation.z, Vector3f(0, 0, 1));

		if (transform_parent)
			return transform_parent->get_transform_matrix() * matrix;
		else
			return matrix;
	}
}