#pragma once

#include "../../maths/Collision.h"

#include "../../app/states/StatePlaying.h"
#include "../../level/tile/Tile.h"

#include "../../util/Log.h"

namespace Physics
{
	bool tileCollision(Object& player)
	{
		for (int x = -1; x < 2; x++)
			for (int y = -1; y < 2; y++)
			{
				int xt = x + player.pos.x / 32;
				int yt = y + player.pos.y / 32;

				Level::TileData data = State::Playing::instance->getLevel().getTiles().getTileData(0, xt, yt);
				if (!(bool)(data.flags & (int32)Level::TileFlags::PASSABLE))
				{
					Manifold* m = new Manifold();
					Object tileObject;
					tileObject.pos = { xt * 32.0f, yt * 32.0f };
					tileObject.aabb = { { 0, 0 }, { 32, 32 } };

					tileObject.density = 0;
					tileObject.restitution = .4f;

					tileObject.initMass();

					m->A = &player;
					m->B = &tileObject;
					AABBtoAABB(m);
					ResolveCollision(*m, player, tileObject);
					PositionalCorrection(*m, player, tileObject);
				}
			}

		return false;
	}
}
