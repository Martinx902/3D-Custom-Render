/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../header/Light.hpp"

namespace MScenary
{
	void Light::update()
	{
		static float movement_aux = 0;
		static int direction = 1; // Initial direction

		if (movement_aux >= 0.7f || movement_aux <= -0.5f)
		{
			direction *= -1; // Change direction
		}

		movement_aux += direction * 0.02f;

		transform->set_position(0.f, movement_aux, 0.f);
	}

	void Light::apply_view_transform(const Matrix44& view_matrix)
	{
		//TODO aplicar un nuevo transform al transform
		transform->get_transform_matrix() = view_matrix * transform->get_transform_matrix();
	}

	float Light::calculate_light_intensity(const Vector3f& point, const Vector3f& normal)
	{
		//LAMBERT MODEL  L ^ N

		Vector3f& l = glm::normalize(transform->get_position() - point);

		float dot_product = glm::dot(l, normal);

		float total_intensity = ambient_intensity + (intensity * dot_product);

		return glm::clamp(total_intensity, ambient_intensity, 1.f);
	}
}