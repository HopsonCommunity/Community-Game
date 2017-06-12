#pragma once

#include "../Common.h"

#include "../util/Random.h"

#include "tile/Tile.h"
#include "../util/Log.h"

namespace Level
{
	struct TileNode;

	// Each tile has one of these
	struct LightData
	{
		Color color;
		byte intensity, absorb;
	};

	// Light emitter
	struct StaticLight
	{
		int32 x, y;
		Color color;
		byte intensity;
	};

	class LightMap
	{
	public:
		int32 width, height;

		LightMap(std::vector<std::vector<TileNode*>>* tiles, int32 width, int32 height);
		~LightMap();

		// Try to rebuild the lighting if a rebuild is requested
		void rebuildLight();
		// Render the light
		void renderLight(sf::RenderWindow& window);

		// Add and remove light sources
		void addStaticLight(StaticLight* light);
		void removeStaticLight(StaticLight* light);

		// Request rebuild of light if a tile or light source changes
		void requestRebuild() { m_requestedRebuild = true; }

	private:
		void resetLight() const;
		void buildLight();

		// Flood tile neighbours with light
		void checkNeighbours(LightData* tile, int32 x, int32 y) const;
		
		// Add intensities to tiles
		void addIntensity(int32 x, int32 y, Color color, byte intensity) const;
		static void setIntensity(LightData* tile, Color color, byte intensity);
		
		// Returns the middle of the tile at x, y
		static Vec2 getTileCenter(int32 x, int32 y) { return Vec2(x * TILE_SIZE, y * TILE_SIZE); }
		// Returns the color of the tile at x, y
		Color getTileLight(int32 x, int32 y) const;

		// Used for rendering
		std::vector<sf::Vertex> m_lightMask;

		bool m_requestedRebuild;
		std::vector<StaticLight*> m_staticLights;

		// Pointer to a TileLayer's tiles list
		std::vector<std::vector<TileNode*>>* m_tiles;
	};
}
