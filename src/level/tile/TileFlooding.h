#pragma once

#include "../../entity/Entity.h"
#include "../../maths/maths.h"

#include <SFML/Graphics.hpp>

#include <vector>

namespace Util
{
	class TileFlooding
	{
	public:
		static std::vector<Entity::Entity*> getAllEntitesNearOtherEntity(Vec2i entityPos, int radius);
		static std::vector<std::pair<Vec2i, int>> tileFlooding(Vec2i entityPos, int radius);
		inline static bool hasCoord(const std::vector<std::pair<Vec2i, int>>& tiles, Vec2i toTest);
	};
}
