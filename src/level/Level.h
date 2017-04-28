#pragma once

#include "Tile/Tile.h"

#include "../entity/system/System.h"
#include "../util/Timestep.h"

#include <iostream>

namespace Framework
{
	class Entity;
	class Player;
}

namespace Level
{
	class Level
	{
        public:
            Level() {}
            Level(unsigned int width, unsigned int height);
			
            void addEntity(std::unique_ptr<Framework::Entity> entity);
            Framework::Entity* getEntity(const uint64& id);

			Framework::Entity* getPlayer() { return player; }

			void setTile(unsigned int x, unsigned int y, Tile::Tile& tile);
            Tile::Tile* getTile(unsigned int x, unsigned int y);
            
            Framework::Entity* getEntityOnTile(unsigned int x, unsigned int y);

			void update(const Timestep& ts);
            void render(sf::RenderWindow& window);

        private:
            uint m_width;
            uint m_height;
            std::vector<Tile::Tile*> m_tiles;

			std::vector<std::unique_ptr<Framework::Entity>> m_entities;

			std::unique_ptr<Framework::System> m_renderSystem;
			std::vector<std::unique_ptr<Framework::System>> m_updateSystems;
		public:
			Framework::Entity* player;
	};
}
