#pragma once

#include "Tile.h"

#include "../../util/Types.h"

#include <SFML/Graphics.hpp>

namespace Level {
namespace Tile
{
	class WallTile : public Tile
	{
		private:
			sf::Sprite m_spriteSide;
			float m_height;

		public:
			WallTile(byte id, sf::Sprite spriteTop, sf::Sprite spriteSide, float height, bool solid);

			void render(uint32 x, uint32 y, Level& level, sf::RenderWindow& window) override;
	};
}}
