#include "TileCollision.h"

#include "TileDatabase.h"

namespace Level
{
	std::pair<bool, bool> tileCollision(Vec2 position, Vec2 velocity, FloatRectangle& bounds, const Timestep& ts)
	{
		const Vec2 dest = position + velocity * ts.asSeconds();

		const Vec2i from = Vec2i((dest + bounds.getMinimumBound()) / TILE_SIZE);
		const Vec2i to = Vec2i((dest + bounds.getMaximumBound()) / TILE_SIZE) + Vec2i{ 2, 2 };

		bool collidingX = false, collidingY = false;
		for (int32 x = from.x; x < to.x; ++x)
			for (int32 y = from.y; y < to.y; ++y)
			{
				if (!State::Playing::get().isTilePassable(0, x, y))
				{
					const FloatRectangle& tileCollisionBox = TileDatabase::get().getTileData(byte(State::Playing::get().getLevel().getTiles().getTile(0, x, y)->id)).bounds;

					FloatRectangle tileBounds;
					tileBounds.position = Vec2((float)x, (float)y) * TILE_SIZE + tileCollisionBox.position;
					tileBounds.size = tileCollisionBox.size;

					if (dest.x + bounds.getMaximumBound().x > tileBounds.x
						&& dest.x + bounds.x < tileBounds.getMaximumBound().x
						&& position.y + bounds.y + bounds.height > tileBounds.y
						&& position.y + bounds.y < tileBounds.getMaximumBound().y)
						collidingX = true;

					if (position.x + bounds.x + bounds.width > tileBounds.x
						&& position.x + bounds.x < tileBounds.getMaximumBound().x
						&& dest.y + bounds.y + bounds.height > tileBounds.y
						&& dest.y + bounds.y < tileBounds.getMaximumBound().y)
						collidingY = true;
				}
			}

		return std::make_pair(collidingX, collidingY);
	}
}
