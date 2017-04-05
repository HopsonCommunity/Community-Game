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
        public:
            Level() {}
            Level(unsigned int width, unsigned int height);

            void addEntity(Framework::Entity* entity);
            void setTile(unsigned int x, unsigned int y, Tile::Tile& tile);
            Tile::Tile* getTile(unsigned int x, unsigned int y);
            void update(const Timestep& ts);
            void render(sf::RenderWindow& window);

        private:
            unsigned int m_width;
            unsigned int m_height;
            std::vector<Tile::Tile*> m_tiles;
            std::vector<Framework::Entity*> m_entities;
	};
}
