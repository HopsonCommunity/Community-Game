#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "../util/Types.h"

namespace Level
{
    class TileMap
    {
        public:
            TileMap(uint32 width, uint32 height, const std::vector<uint8>& tileData);

            void draw(sf::RenderWindow& window);

        private:
            void addTile(int32 x, int32 y, int8 tileType);

            std::vector<uint8>      m_tileData; //1 byte per tile
            std::vector<sf::Vertex> m_vertexArray;

            uint32 m_width  = 0;
            uint32 m_height = 0;
    };
}
