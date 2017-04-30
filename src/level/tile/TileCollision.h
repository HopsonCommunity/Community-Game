#pragma once

#include "../../maths/Hitbox.h"

#include "../../app/states/StatePlaying.h"
#include "../../level/Tile/Tile.h"

#include <map>

namespace Physics
{
	bool tileCollision(const sf::Vector2i& position, const Hitbox& hitBox)
	{
		for (int c = 0; c < 4; c++)
		{
			int xt = int(-hitBox.xMin + position.x + c % 2 * hitBox.xMax) >> 5;
			int yt = int(-hitBox.yMin + position.y + c / 2 * hitBox.yMax) >> 5;

			if (!(bool)(State::Playing::instance->getLevel().getTiles().getTileData(0, xt, yt).flags & (int32)Level::TileFlags::PASSABLE))
				return true;
		}

		return false;
	}
}
