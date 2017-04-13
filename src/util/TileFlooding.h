#include <vector>
#include "../Entity/Entity.h"
#include "../level/Level.h"
#include <SFML/Graphics.hpp>

namespace Util
{
    typedef sf::Vector2<int32> Vec2i;

    class TileFlooding
    {
    public:
        static std::vector<Framework::Entity*> getAllEntitesNearOtherEntity(Vec2i entityPos, int radius, Level::Level* level);
        static std::vector<std::pair<Vec2i, int>> tileFlooding(Vec2i entityPos, int radius, Level::Level* level);
        inline static bool hasCoord(const std::vector<std::pair<Vec2i, int>>& tiles, Vec2i toTest);
    };
}