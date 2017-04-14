#pragma once

#include <map>

#include "Hitbox.h"

#include "../../level/Level.h"
#include "../../level/Tile/Tile.h"

namespace Physics
{
	bool tileCollision(const sf::Vector2i& position, const Hitbox& hitBox, Level::Level& level)
	{
		for (int c = 0; c < 4; c++)
		{
			int xt = int(position.x - c % 2 * hitBox.xMax + hitBox.xMin) >> 5;
			int yt = int(position.y - c / 2 * hitBox.yMax + hitBox.yMin) >> 5;
			if (level.getTile(xt, yt) != nullptr && level.getTile(xt, yt)->isSolid())
				return true;
		}

		return false;
	}
}
