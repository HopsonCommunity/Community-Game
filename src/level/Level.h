#pragma once

#include "Tile/Tile.h"
#include <iostream>
#include "../util/Timestep.h"

namespace Framework
{
	class Entity;
}

namespace Level
{

	class Level
	{
	private:
		unsigned int m_width;
		unsigned int m_height;
		std::vector<Tile::Tile*> m_tiles;
		std::vector<Framework::Entity*> m_entities;

	public:
		Level() {}
		Level(unsigned int width, unsigned int height);

		void addEntity(Framework::Entity* entity);
		void setTile(unsigned int x, unsigned int y, Tile::Tile& tile);
		inline Tile::Tile* getTile(unsigned int x, unsigned int y)
		{
			if (x < 0 || x >= m_width || y < 0 || y >= m_height) return nullptr;
			return m_tiles[x + y * m_width];
		}

		void update(const Timestep& ts);
		void render(sf::RenderWindow& window);
	};

}
