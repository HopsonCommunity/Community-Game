#include "WallTile.h"

#include "../LevelRenderer.h"
#include <iostream>

namespace Level
{
	namespace Tile
	{

		WallTile::WallTile(uint8 id, sf::Sprite spriteTop, sf::Sprite spriteSide, float height, bool solid)
			: Tile(id, spriteTop, solid),
			m_spriteSide(spriteSide),
			m_height(height)
		{}

		void WallTile::render(uint32 x, uint32 y, sf::RenderWindow& window)
		{
			LevelRenderer::renderWallTileTop(x * TILE_SIZE, y * TILE_SIZE, 32, m_sprite);
			LevelRenderer::renderWallTileSide(x * TILE_SIZE, y * TILE_SIZE, m_spriteSide);
		}

	}
}