#pragma once

#include "../../level/Level.h"
#include "../../level/Tile/Tile.h"

namespace Physics
{

	bool* tileCollision(sf::Vector2f& position, sf::Vector2f& velocity, HitBox& hitBox, Level::Level& level, float dt)
	{
		int tileX0 = (int)((position.x + velocity.x * dt + hitBox.m_rect.left) / Level::TILE_SIZE);
		int tileX1 = (int)((position.x + velocity.x * dt + hitBox.m_rect.left + hitBox.m_rect.width) / Level::TILE_SIZE) + 2;
		int tileY0 = (int)((position.y + velocity.y * dt + hitBox.m_rect.top) / Level::TILE_SIZE);
		int tileY1 = (int)((position.y + velocity.y * dt + hitBox.m_rect.top + hitBox.m_rect.height) / Level::TILE_SIZE) + 2;

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

					if (position.x + velocity.x * dt + hitBox.m_rect.left + hitBox.m_rect.width > x0
						&& position.x + velocity.x * dt + hitBox.m_rect.left < x1
						&& position.y + hitBox.m_rect.top + hitBox.m_rect.height > y0
						&& position.y + hitBox.m_rect.top < y1)
						collidingX = true;

					if (position.x + hitBox.m_rect.left + hitBox.m_rect.width > x0
						&& position.x + hitBox.m_rect.left < x1
						&& position.y + velocity.y * dt + hitBox.m_rect.top + hitBox.m_rect.height > y0
						&& position.y + velocity.y * dt + hitBox.m_rect.top < y1)
						collidingY = true;
				}
			}
		}

		bool result[2];
		result[0] = collidingX;
		result[1] = collidingY;

		return result;
	}

}
