#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "../../util/Types.h"

namespace Level{
namespace Tile
{
    class Map
    {
        //Each tile of the tile map = one quad
        //A quad has four vertex points, as marked by the vertex names
        struct Quad
        {
            sf::Vertex topLeft;
            sf::Vertex topRight;
            sf::Vertex bottomLeft;
            sf::Vertex bottomRight;
        };

        public:
            Map(const std::vector<uint8>& tileData, uint32 width, uint32 height);

            void draw(sf::RenderWindow& window);

        private:
            void addTile                (float x, float y, int8 tileType);
            void setQuadVertexCoords    (Quad& quad, float x, float y);
            void setQuadTextureCoords   (Quad& quad, int8 tileType);

            std::vector<uint8>      m_tileData; //1 byte per tile
            std::vector<sf::Vertex> m_vertexArray;

            uint32 m_width  = 0;
            uint32 m_height = 0;

            sf::Texture m_tileTextures;
    };
}}
