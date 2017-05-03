#pragma once

#include "../../maths/AABB.h"

#include "../../app/states/StatePlaying.h"
#include "../../level/tile/Tile.h"

namespace Physics
{
	std::pair<bool, bool> tileCollision(Vec2 position, Vec2 velocity, AABB& hitBox, float dt)
	{
		int tileX0 = (int)((position.x + velocity.x * dt + hitBox.min.x) / TILE_SIZE);
		int tileX1 = (int)((position.x + velocity.x * dt + hitBox.min.x + hitBox.max.x) / TILE_SIZE) + 2;
		int tileY0 = (int)((position.y + velocity.y * dt + hitBox.min.y) / TILE_SIZE);
		int tileY1 = (int)((position.y + velocity.y * dt + hitBox.min.y + hitBox.max.y) / TILE_SIZE) + 2;

		bool collidingX = false;
		bool collidingY = false;
		for (int x = tileX0; x < tileX1; x++)
		{
			for (int y = tileY0; y < tileY1; y++)
			{
				Level::TileData data = State::Playing::instance->getLevel().getTiles().getTileData(0, x, y);
				if (!(bool)(data.flags & (int32)Level::TileFlags::PASSABLE))
				{
					float x0 = x * TILE_SIZE;
					float y0 = y * TILE_SIZE;
					float x1 = x0 + TILE_SIZE;
					float y1 = y0 + TILE_SIZE;

					if (position.x + velocity.x * dt + hitBox.min.x + hitBox.max.x > x0
						&& position.x + velocity.x * dt + hitBox.min.x < x1
						&& position.y + hitBox.min.y + hitBox.max.y > y0
						&& position.y + hitBox.min.y < y1)
						collidingX = true;
	
					if (position.x + hitBox.min.x + hitBox.max.x > x0
						&& position.x + hitBox.min.x < x1
						&& position.y + velocity.y * dt + hitBox.min.y + hitBox.max.y > y0
						&& position.y + velocity.y * dt + hitBox.min.y < y1)
						collidingY = true;
				}
			}
		}

		return std::make_pair(collidingX, collidingY);
	}
}
