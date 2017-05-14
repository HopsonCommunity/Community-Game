#pragma once

#include "../../Common.h"

#include "../../maths/Random.h"

#include "Tile.h"
#include "../LightMap.h"

namespace Level
{
	struct TileNode
	{
		TileID id;
		byte metadata;
		LightData light;
	};

    class TileMap
    {
	public:
		typedef std::vector<std::tuple<uint, uint, byte, byte>> AddList;
	private:
        struct TileLayer
        {
            std::vector<std::vector<TileNode*>> tiles;
			std::vector<sf::Vertex> vertexArray;
        };
	
	public:
        TileMap(uint width, uint height);
		~TileMap();

        void addLayer();
        void addTile(uint layer, uint x, uint y, byte id, byte metadata);
		void addTiles(uint layer, const AddList& tiles);

		void render(sf::RenderWindow& window);

		LightMap* getLightMap() const { return m_lmap; }
		TileNode* getTile(uint layer, uint x, uint y);

        uint width;
        uint height;
   
	private:
		LightMap* m_lmap;

		void qAddTile(uint layer, uint x, uint y, byte id, byte metadata);

		void generateVertexArray(byte layer);
	    static void addTileVertices(TileLayer* layer, uint x, uint y, TileNode* tile);

		sf::RenderStates m_renderState;
		std::vector<std::unique_ptr<TileLayer>> m_layers;
    };
}
