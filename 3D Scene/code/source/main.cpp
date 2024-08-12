/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

  /* ---------------------------------/
  |*        ---CONTROLS---            |
  |*                                  |
  |*      WASD - Camera Panning       |
  |*      Q/E - Zoom Out/In           |
  |*      Arrows - Rotation           |
  |*      R - Reset Camera            |
  |*								  |
  /----------------------------------*/

#include "../header/Scene.hpp"

using namespace MScenary;

int main()
{
	constexpr auto window_width = 800u;
	constexpr auto window_height = 800u;

	Scene scene(window_width, window_height);

	scene.run();

	return 1;
}