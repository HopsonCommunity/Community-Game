#pragma once

#include "../entity/Entity.h"
#include "../level/Level.h"
#include "../maths/Maths.h"

#include <SFML/Graphics.hpp>

#include <vector>

namespace Util
{
    class TileFlooding
    {
    public:
        static std::vector<Framework::Entity*> getAllEntitesNearOtherEntity(Vec2i entityPos, int radius, Level::Level* level);
        static std::vector<std::pair<Vec2i, int>> tileFlooding(Vec2i entityPos, int radius, Level::Level* level);
        inline static bool hasCoord(const std::vector<std::pair<Vec2i, int>>& tiles, Vec2i toTest);
    };
}
