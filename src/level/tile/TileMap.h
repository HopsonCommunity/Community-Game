#pragma once

#include "../../Common.h"

#include "Tile.h"

namespace Level
{
#define TILE_ID 0
#define TILE_METADATA 1

    class TileMap
    {
	public:
		typedef std::tuple<byte, byte> TileNode;
		typedef std::vector<std::tuple<uint, uint, byte, byte>> AddList;
	private:
		struct Quad
        {
            sf::Vertex topLeft;
            sf::Vertex topRight;
            sf::Vertex bottomLeft;
            sf::Vertex bottomRight;
        };
        struct TileLayer
        {
            std::vector<std::vector<TileNode>> tiles;
			std::vector<sf::Vertex> vertexArray;
        };

    public:
        TileMap(uint width, uint height);

        void addLayer();
        void addTile(uint layer, uint x, uint y, byte id, byte metadata);
		void addTiles(uint layer, const AddList& tiles);

        void render(sf::RenderWindow& window);

        TileData getTileData(uint layer, uint x, uint y);

        uint width;
        uint height;
    private:

		void qAddTile(uint layer, uint x, uint y, byte id, byte metadata);

		void generateVertexArray(byte layer);
        void addTileVertices(byte layer, uint x, uint y, TileNode tile);
		void setQuadTextureCoords(TileMap::Quad &quad, TileNode tile);
		void setQuadVertexCoords(TileMap::Quad &quad, float x, float y, TileNode tile);

        std::vector<std::unique_ptr<TileLayer>> m_layers;
        const sf::Texture* m_atlas;
    };
}
