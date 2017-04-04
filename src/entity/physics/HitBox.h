#pragma once

#include "SFML/Graphics.hpp"

namespace Physics
{

	class HitBox
	{
	public:
		sf::FloatRect m_rect;

		HitBox(sf::FloatRect rect);
	};

}
