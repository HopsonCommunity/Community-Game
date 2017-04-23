#pragma once

#include <vector>
#include "../../Types.h"
#include "Tile.h"

namespace Level
{
    class TileMapNode
    {
    public:
        TileMapNode(byte ID) : m_ID(ID), m_metadata(0) {};
        TileMapNode(byte ID, byte metadata) : m_ID(ID), m_metadata(metadata) {};

        byte getID() { return m_ID; };
        byte getMetadata() { return m_metadata; };
    private:
        byte m_ID;
        byte m_metadata;
    };

    class TileMap
    {
        struct Quad
        {
            sf::Vertex topLeft;
            sf::Vertex topRight;
            sf::Vertex bottomLeft;
            sf::Vertex bottomRight;
        };
        struct TileLayer
        {
            std::vector<std::vector<TileMapNode> > tiles;
        };

    public:
        TileMap();
        TileMap(uint width, uint height);

        void addLayer();
        void addTile(uint layer, uint x, uint y, byte id, byte metadata);
        void draw(sf::RenderWindow& window);

        TileData getTileData(uint layer, uint x, uint y);

        uint width;
        uint height;
    private:

        void generateVertexArray(byte layer);
        void addTileVertices(byte layer, uint x, uint y, TileMapNode tile);

        void setQuadTextureCoords(Quad& quad, TileMapNode tile);
        void setQuadVertexCoords(Quad& quad, int x, int y, TileMapNode tile);

        std::vector<TileLayer> m_layers;
        std::vector<sf::VertexArray> m_vertexArrays;
        const sf::Texture *m_tileTexture;
    };
}
