#include "TileMap.h"

#include "../../util/Random.h"
#include "../LevelConstants.h"
#include "TileDatabase.h"

#include <iostream>

///@TODO Remove this
namespace
{
    std::vector<uint8> tiles =
    {
        1, 0, 1, 3, 1,
        3, 0, 3, 1, 3,
        1, 0, 0, 0, 1,
        3, 1, 0, 1, 3,
        1, 3, 1, 3, 1,
    };
}

namespace Level{
namespace Tile
{
    Map::Map()
    :   m_tileData  (tiles)
    ,   m_width     (5)
    ,   m_height    (5)
    {
        m_tileTextures.loadFromFile("res/textures/tile_atlas.png");
        generateVertexArray();
    }

    Map::Map(const std::vector<uint8>& tileData,
                     uint32 width,
                     uint32 height)
    :   m_tileData  (tileData)
    ,   m_width     (width)
    ,   m_height    (height)
    {
        m_tileTextures.loadFromFile("res/textures/tile_atlas.png");
        generateVertexArray();
    }

    void Map::draw(sf::RenderWindow& window)
    {
		generateVertexArray();

        sf::RenderStates states;
        states.texture = &m_tileTextures;

        window.draw(m_vertexArray.data(), m_vertexArray.size(), sf::Quads, states);
    }

    uint8 Map::getTile(uint32 x, uint32 y)
    {
        return m_tileData.at(y * m_width + x);
    }

    void Map::generateVertexArray()
    {
        m_vertexArray.reserve(m_width * m_height * 4);
        for (uint32 y = 0; y < m_height; ++y)
        {
            for (uint32 x = 0; x < m_width; ++x)
            {
                addTile(x * TILE_SIZE, y * TILE_SIZE, getTile(x, y));
            }
        }
    }

    void Map::addTile(float x, float y, int8 tileType)
    {
        Quad quad;

        //Set the positions of the 4 verticies of the quad
        setQuadVertexCoords (quad, x, y);
        setQuadTextureCoords(quad, tileType);

        //Add them into the array (in anti-clockwise order)
        m_vertexArray.push_back(quad.topLeft);
        m_vertexArray.push_back(quad.topRight);
        m_vertexArray.push_back(quad.bottomRight);
        m_vertexArray.push_back(quad.bottomLeft);
    }

    void Map::setQuadVertexCoords(Quad& quad, float x, float y)
    {
        //Set the vertex positions, anti-clockwise order
        quad.topLeft     .position = {x,              y};
        quad.topRight    .position = {x + TILE_SIZE,  y};
        quad.bottomRight .position = {x + TILE_SIZE,  y + TILE_SIZE};
        quad.bottomLeft  .position = {x,              y + TILE_SIZE};
    }

    void Map::setQuadTextureCoords(Quad& quad, int8 tileType)
    {
        //Get the place inside of the texture atlas where the texture can be found
        auto texCoords = Tile::Database::get().getTileData(tileType).texCoords;

        //Get the number of texture variations
        auto texVaritations = Tile::Database::get().getTileData(tileType).textureVariations;
        //Choose a random variation

        auto varitation = Random::intInRange(0, texVaritations - 1);

        //Get the x and y positions inside of the texture atlas of that variation of the texture
        auto tx = texCoords.x + varitation * TILE_SIZE;
        auto ty = texCoords.y * TILE_SIZE;

        //Set texture coords of the 4 vertex points, anti-clockwise order
        quad.topLeft     .texCoords = {tx,              ty};
        quad.topRight    .texCoords = {tx + TILE_SIZE,  ty};
        quad.bottomRight .texCoords = {tx + TILE_SIZE,  ty + TILE_SIZE};
        quad.bottomLeft  .texCoords = {tx,              ty + TILE_SIZE};
    }

}}
