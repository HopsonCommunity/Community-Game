#pragma once

#include "../../util/Types.h"
#include <SFML/Graphics.hpp>
#include "Tile.h"

namespace Level
{
	namespace Tile
	{

		class Tile;

		class WallTile : public Tile
		{
		private:
			sf::Sprite m_spriteSide;
			float m_height;

		public:
			WallTile(uint8 id, sf::Sprite spriteTop, sf::Sprite spriteSide, float height);

			void render(uint32 x, uint32 y, sf::RenderWindow& window);
		};

	}
}
