/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../header/Camera.hpp"
#include "../header/Scene.hpp"

namespace MScenary
{
	Camera::Camera
	(
		Scene* given_scene,
		float fov,
		float near_d,
		float far_d,
		float given_movement_speed,
		float given_rotation_speed
	)
		:
		movement_speed(given_movement_speed),
		rotation_speed(given_rotation_speed),
		Node(given_scene)
	{
		perspective_matrix = perspective(fov, near_d, far_d, float(scene->get_window_width() / scene->get_window_height()));
	}

	void Camera::update()
	{
		static float pos_x = transform->get_position().x;
		static float pos_y = transform->get_position().y;
		static float pos_z = transform->get_position().z;

		static float rot_x = transform->get_rotation().x;
		static float rot_y = transform->get_rotation().y;

		movement_input(pos_y, pos_x, pos_z);

		rotation_input(rot_x, rot_y);

		//Reset the camera
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			pos_x = pos_y = pos_z = 0;
			rot_x = rot_y = 0;
		}

		transform->set_position(pos_x, pos_y, pos_z);
		transform->set_rotation(rot_x, rot_y, 0.f);
	}

	void Camera::rotation_input(float& rot_x, float& rot_y)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			rot_x -= rotation_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			rot_x += rotation_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			rot_y -= rotation_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			rot_y += rotation_speed;
		}
	}

	void Camera::movement_input(float& pos_y, float& pos_x, float& pos_z)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			pos_y -= movement_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			pos_x -= movement_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			pos_y += movement_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			pos_x += movement_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			pos_z += movement_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			pos_z -= movement_speed;
		}
	}

	Matrix44 Camera::get_view_matrix()
	{
		return inverse(transform->get_transform_matrix());
	}
	Matrix44 Camera::get_projection_matrix()
	{
		return perspective_matrix * get_view_matrix();
	}
}