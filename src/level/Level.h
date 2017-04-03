#pragma once

#include "Tile/Tile.h"
#include "../entity/Entity.h"

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

		void update(float dt);
		void render(sf::RenderWindow& window);
	};

}
