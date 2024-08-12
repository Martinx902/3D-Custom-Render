#include "../header/Ship.hpp"

namespace MScenary
{
	void Ship::update()
	{
		static float movement_aux = 0;
		static int direction = 1; // Initial direction
		static float angle = 0;

		angle += movement_speed;

		if (movement_aux >= 0 || movement_aux <= -ping_pong_movement)
		{
			direction *= -1;  //Change direction
		}

		movement_aux += direction * movement_speed;

		transform->set_position(1.f, movement_aux, 3.f);
		transform->set_rotation(0.f, angle * 0.8f, 0.f);
	}
}