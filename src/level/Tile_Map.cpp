#include "Tile_Map.h"

namespace Level
{
    TileMap::TileMap(const std::vector<uint8>& tileData,
                     uint32 width,
                     uint32 height)
    :   m_tileData  (tileData)
    ,   m_width     (width)
    ,   m_height    (height)
    {
        m_vertexArray.reserve(width * height * 4);
    }

    void TileMap::draw(sf::RenderWindow& window)
    {

    }

    void TileMap::addTile(int32 x, int32 y, int8 tileType)
    {

    }
}
