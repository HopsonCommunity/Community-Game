#pragma once

#include "../Common.h"

#include "../maths/Random.h"

#include "tile/Tile.h"

namespace Level
{
	struct TileNode;

	struct LightData
	{
		sf::Color color;
		byte intensity, absorb;
	};

	class LightMap
	{
	public:
		uint width, height;
		bool Dirty, Built;

		LightMap(std::vector<std::vector<TileNode*>>* tiles, uint width, uint height);

		void rebuildLight();

		void resetLight();
		
		void buildLight();
		void checkNeighbours(LightData* tile, uint x, uint y) const;
		void addIntensity(uint x, uint y, sf::Color color, byte intensity);
		void setIntensity(LightData* tile, sf::Color color, byte intensity) const;

		void renderLight(sf::RenderWindow& window);
		
		// Returns the middle of the tile at x, y
		static Vec2 getTileCenter(int32 x, int32 y) { return Vec2(x * TILE_SIZE + TILE_SIZE * .5f, y * TILE_SIZE + TILE_SIZE * .5f); }

	private:
		LightData **lightTiles[LIGHT_MAX_LIGHTLEVEL];
		int lightCounts[LIGHT_MAX_LIGHTLEVEL];

		std::vector<sf::Vertex> m_lightMask;
		std::vector<std::vector<TileNode*>>* m_tiles;
	};
}