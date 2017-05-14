#pragma once

#include "../../maths/AABB.h"

#include "../../app/states/StatePlaying.h"
#include "../../level/tile/Tile.h"

namespace Level
{
	std::pair<bool, bool> tileCollision(Vec2 position, Vec2 velocity, AABB& hitBox, const Timestep& ts)
	{
		Vec2 dest = position + velocity * ts.asSeconds();
		int tileX0 = (int)((dest.x + hitBox.min.x) / TILE_SIZE);
		int tileX1 = (int)((dest.x + hitBox.min.x + hitBox.max.x) / TILE_SIZE) + 2;
		int tileY0 = (int)((dest.y + hitBox.min.y) / TILE_SIZE);
		int tileY1 = (int)((dest.y + hitBox.min.y + hitBox.max.y) / TILE_SIZE) + 2;

		bool collidingX = false, collidingY = false;
		for (int x = tileX0; x < tileX1; x++)
			for (int y = tileY0; y < tileY1; y++)
			{
				if (!State::Playing::instance->isTilePassable(0, x, y))
				{
					float x0 = x * TILE_SIZE, y0 = y * TILE_SIZE;
					float x1 = x0 + TILE_SIZE, y1 = y0 + TILE_SIZE;

					if (dest.x + hitBox.min.x + hitBox.max.x > x0
						&& dest.x + hitBox.min.x < x1
						&& position.y + hitBox.min.y + hitBox.max.y > y0
						&& position.y + hitBox.min.y < y1)
						collidingX = true;
	
					if (position.x + hitBox.min.x + hitBox.max.x > x0
						&& position.x + hitBox.min.x < x1
						&& dest.y + hitBox.min.y + hitBox.max.y > y0
						&& dest.y + hitBox.min.y < y1)
						collidingY = true;
				}
			}

		return std::make_pair(collidingX, collidingY);
	}
}
