/**
  * @author    Martin P�rez Villabrille
  * @copyright Copyright (c) 2023+ Martin P�rez Villabrille.
  *            All rights reserved
  */

#pragma once

#include <SFML/Graphics/Color.hpp>

namespace MScenary
{
	//Not being currently used
	class Material
	{
		sf::Color baseColor;

	public:

		Material(float r, float g, float b)
		{
			baseColor.r = r;
			baseColor.g = g;
			baseColor.b = b;
		}
	};
}