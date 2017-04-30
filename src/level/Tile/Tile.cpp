#include "Tile.h"

namespace Level
{
	Tile::Tile(byte id, int32 flags, sf::IntRect texture)
		: m_data({id, flags, texture}) // ARE YOU **$& SERIOUS
	{
	}

	TileDefault::TileDefault(byte id, int32 flags, sf::IntRect texture)
		: Tile(id, flags, texture)
	{
	}

	void TileDefault::render(uint32 x, uint32 y, Level& level, sf::RenderWindow& window)
	{
		///TODO: Render when level is ready
		// Render a normal tile
	}
}