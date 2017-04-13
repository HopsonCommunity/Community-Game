#pragma once

#include <map>

#include "../../level/Level.h"
#include "../../level/Tile/Tile.h"

namespace Physics
{
	bool tileCollision(sf::Vector2f& position, sf::FloatRect& hitBox, Level::Level& level)
	{
		/*
		int tileX0 = (int)((position.x + velocity.x * dt) / Level::TILE_SIZE);
		int tileX1 = (int)((position.x + velocity.x * dt) / Level::TILE_SIZE) + 2;
		int tileY0 = (int)((position.y + velocity.y * dt) / Level::TILE_SIZE);
		int tileY1 = (int)((position.y + velocity.y * dt) / Level::TILE_SIZE) + 2;

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
		*/

		bool colliding = false;

		for (int c = 0; c < 4; c++)
		{
			int xt = int(hitBox.left + position.x - c % 2 * hitBox.width) >> 5;
			int yt = int(hitBox.top + position.y - c / 2 * hitBox.height) >> 5;
			if (level.getTile(xt, yt)->isSolid())
				colliding = true;
		}

		return colliding;
	}

}
