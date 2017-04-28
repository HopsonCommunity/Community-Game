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
        struct TileLayer
        {
            std::vector<std::vector<TileMapNode>> tiles;
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

		sf::Vertex* m_buffer;
		uint m_indexCount;

        void generateVertexArray(byte layer);
        void addTileVertices(byte layer, uint x, uint y, TileMapNode tile);

        std::vector<TileLayer> m_layers;
        const sf::Texture* m_tileTexture;
    };
}
