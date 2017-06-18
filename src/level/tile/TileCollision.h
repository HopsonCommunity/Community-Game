#pragma once

#include "../../maths/Rectangle.h"

#include "../../app/states/StatePlaying.h"
#include "../../level/tile/Tile.h"

namespace Level
{
	std::pair<bool, bool> tileCollision(Vec2 position, Vec2 velocity, FloatRectangle& bounds, const Timestep& ts);
}
