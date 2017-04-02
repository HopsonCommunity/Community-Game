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
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };
}

namespace Level{
namespace Tile
{
    Map::Map(const std::vector<uint8>& tileData,
                     uint32 width,
                     uint32 height)
    :   m_tileData  (tiles)  ///@TODO Use the consturcor args here
    ,   m_width     (5)
    ,   m_height    (5)
    {
        m_tileTextures.loadFromFile("res/textures/tile_atlas.png");

        m_vertexArray.reserve(width * height * 4);

        for (uint32 y = 0; y < height; ++y)
        {
            for (uint32 x = 0; x < width; ++x)
            {
                addTile(x * TILE_SIZE, y * TILE_SIZE, 0);
            }
        }
    }

    void Map::draw(sf::RenderWindow& window)
    {
        sf::RenderStates states;
        states.texture = &m_tileTextures;

        window.draw(m_vertexArray.data(), m_vertexArray.size(), sf::Quads, states);
    }

    void Map::addTile(float x, float y, int8 tileType)
    {
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

        //Get the place inside of the texture atlas where the texture can be found
        auto texCoords = Tile::Database::get().getTileData(tileType).texCoords;
        //Get the number of texture variations
        auto texVaritations = Tile::Database::get().getTileData(tileType).textureVariations;
        //Choose a random variation
        auto varitation = Random::intInRange(0, texVaritations - 1);

        std::cout << varitation << std::endl;
        //Get the x and y positions inside of the texture atlas of that variation of the texture
        auto tx = texCoords.x + varitation * TILE_SIZE;
        auto ty = texCoords.y;

        //Set texture coords of the 4 vertex points
        topLeft     .texCoords = {tx,              ty};
        topRight    .texCoords = {tx + TILE_SIZE,  ty};
        bottomRight .texCoords = {tx + TILE_SIZE,  ty + TILE_SIZE};
        bottomLeft  .texCoords = {tx,              ty + TILE_SIZE};

        //Add them into the array (in anti-clockwise order)
        m_vertexArray.push_back(topLeft);
        m_vertexArray.push_back(topRight);
        m_vertexArray.push_back(bottomRight);
        m_vertexArray.push_back(bottomLeft);
    }
}}
