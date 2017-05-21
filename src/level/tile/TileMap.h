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
			LightMap* lightMap;
            std::vector<std::vector<TileNode*>> tiles;
			std::vector<sf::Vertex> vertexArray;

			~TileLayer()
			{
				for (uint i = 0; i < tiles.size(); i++)
					tiles[i].clear();

				delete lightMap;
			}
        };
	
	public:
        TileMap(uint width, uint height);
		~TileMap();

        void addLayer();
        void addTile(uint layer, uint x, uint y, byte id, byte metadata);
		void addTiles(uint layer, const AddList& tiles);
		
		void addStaticLight(uint layer, StaticLight* light);
		void removeStaticLight(uint layer, StaticLight* light);
		void requestRebuild(uint layer);

		void light();
		void render(sf::RenderWindow& window);
		
		TileNode* getTile(uint layer, uint x, uint y);

        uint width;
        uint height;
   
	private:
		void qAddTile(uint layer, uint x, uint y, byte id, byte metadata);

		void generateVertexArray(byte layer);
	    static void addTileVertices(TileLayer* layer, uint x, uint y, TileNode* tile);

		sf::RenderStates m_renderState;
		std::vector<TileLayer*> m_layers;
    };
}
