#include "WallTile.h"

#include "../Level.h"
#include "../LevelRenderer.h"

#include <iostream>

namespace Level {
namespace Tile
{
	WallTile::WallTile(byte id, sf::Sprite spriteTop, sf::Sprite spriteSide, float height, bool solid)
		: Tile(id, spriteTop, solid),
		m_spriteSide(spriteSide),
		m_height(height)
	{}

	void WallTile::render(uint32 x, uint32 y, Level& level, sf::RenderWindow& window)
	{
		LevelRenderer::renderWallTileTop(x * static_cast<uint32>(TILE_SIZE), y * static_cast<uint32>(TILE_SIZE), m_height, m_sprite);
		Tile* nextTile = level.getTile(x, y + 1);
		if (nextTile == nullptr || !nextTile->isSolid() || (nextTile->isSolid() && ((WallTile*)nextTile)->m_height < m_height))
		{
			m_spriteSide.setScale(1, m_height / m_spriteSide.getTextureRect().height);
			LevelRenderer::renderWallTileSide(x * static_cast<uint32>(TILE_SIZE), y * static_cast<uint32>(TILE_SIZE), m_spriteSide, m_height);
		}
	}
}}