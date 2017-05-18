#pragma once

#include "../Common.h"

#include "../maths/Random.h"

#include "tile/Tile.h"
#include "../util/Log.h"

namespace Level
{
	struct TileNode;

	struct LightData
	{
		sf::Color color;
		byte intensity, absorb;
	};

	struct StaticLight
	{
		uint x, y;
		sf::Color color;
		byte intensity;
	};

	inline bool operator==(const StaticLight& left, const StaticLight& other)
	{
		return left.x == other.x && left.y == other.y && left.color == other.color && left.intensity == other.intensity;
	}

	class LightMap
	{
	public:
		int32 width, height;

		LightMap(std::vector<std::vector<TileNode*>>* tiles, int32 width, int32 height);

		void rebuildLight();
		void renderLight(sf::RenderWindow& window);

		void resetLight() const;
		
		void buildLight();
		void checkNeighbours(LightData* tile, uint x, uint y) const;
		
		void addIntensity(uint x, uint y, sf::Color color, byte intensity) const;
		static void setIntensity(LightData* tile, sf::Color color, byte intensity);

		void addStaticLight(StaticLight* light);
		void removeStaticLight(StaticLight* light);

		void requestRebuild() { m_requestedRebuild = true; }
		
		// Returns the middle of the tile at x, y
		static Vec2 getTileCenter(int32 x, int32 y) { return Vec2(x * TILE_SIZE + TILE_SIZE * .5f, y * TILE_SIZE + TILE_SIZE * .5f); }
		sf::Color getTileLight(int32 x, int32 y) const;

	private:
		std::vector<sf::Vertex> m_lightMask;

		bool m_requestedRebuild;
		std::vector<StaticLight*> m_staticLights;

		std::vector<std::vector<TileNode*>>* m_tiles;
	};
}
