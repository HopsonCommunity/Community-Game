#pragma once

#include "Hitbox.h"

#include "../../states/StatePlaying.h"
#include "../../level/Level.h"
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
			if (State::SPlaying::instance->m_level.getTile(xt, yt) != nullptr && State::SPlaying::instance->m_level.getTile(xt, yt)->isSolid())
				return true;
		}

		return false;
	}
}
