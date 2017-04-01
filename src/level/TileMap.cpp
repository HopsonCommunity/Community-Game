#include "TileMap.h"

#include "LevelConstants.h"

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

        for (uint32 y = 0; y < height; ++y)
        {
            for (uint32 x = 0; x < width; ++x)
            {
                addTile(x * TILE_SIZE, y * TILE_SIZE, 0);
            }
        }
    }

    void TileMap::draw(sf::RenderWindow& window)
    {
        window.draw(m_vertexArray.data(), m_vertexArray.size(), sf::Quads);
    }

    void TileMap::addTile(float x, float y, int8 tileType)
    {
        ///@TODO Textures
        //4 points of a quad
        sf::Vertex topLeft;
        sf::Vertex topRight;
        sf::Vertex bottomLeft;
        sf::Vertex bottomRight;

        //Set the positions of the 4 verticies of the quad
        topLeft     .position = {x,              y};
        topRight    .position = {x + TILE_SIZE,  y};
        bottomRight .position = {x + TILE_SIZE,  y + TILE_SIZE};
        bottomLeft  .position = {x,              y + TILE_SIZE};

        //Add them into the array (in anti-clockwise order)
        m_vertexArray.push_back(topLeft);
        m_vertexArray.push_back(topRight);
        m_vertexArray.push_back(bottomRight);
        m_vertexArray.push_back(bottomLeft);
    }
}
