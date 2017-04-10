#pragma once

#include <map>

#include "../../level/Level.h"
#include "../../level/Tile/Tile.h"

namespace Physics
{

	std::pair<bool, bool> tileCollision(sf::Vector2f& position, sf::Vector2f& velocity, sf::FloatRect& hitBox, Level::Level& level, float dt)
	{
		int tileX0 = (int)((position.x + velocity.x * dt + hitBox.left) / Level::TILE_SIZE);
		int tileX1 = (int)((position.x + velocity.x * dt + hitBox.left + hitBox.width) / Level::TILE_SIZE) + 2;
		int tileY0 = (int)((position.y + velocity.y * dt + hitBox.top) / Level::TILE_SIZE);
		int tileY1 = (int)((position.y + velocity.y * dt + hitBox.top + hitBox.height) / Level::TILE_SIZE) + 2;

		bool collidingX = false;
		bool collidingY = false;
		for (int x = tileX0; x < tileX1; x++)
		{
			for (int y = tileY0; y < tileY1; y++)
			{
				Level::Tile::Tile* tile = level.getTile(x, y);

				if (tile != nullptr && tile->isSolid())
				{
					float x0 = x * Level::TILE_SIZE;
					float y0 = y * Level::TILE_SIZE;
					float x1 = x0 + Level::TILE_SIZE;
					float y1 = y0 + Level::TILE_SIZE;

					if (position.x + velocity.x * dt + hitBox.left + hitBox.width > x0
						&& position.x + velocity.x * dt + hitBox.left < x1
						&& position.y + hitBox.top + hitBox.height > y0
						&& position.y + hitBox.top < y1)
						collidingX = true;

					if (position.x + hitBox.left + hitBox.width > x0
						&& position.x + hitBox.left < x1
						&& position.y + velocity.y * dt + hitBox.top + hitBox.height > y0
						&& position.y + velocity.y * dt + hitBox.top < y1)
						collidingY = true;
				}
			}
		}

		return std::make_pair(collidingX, collidingY);
	}

}
