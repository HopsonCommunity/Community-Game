#pragma once

#include "Tile/Tile.h"

#include "../entity/system/System.h"
#include "../util/Timestep.h"

#include <iostream>

namespace Entity
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
			
            void addEntity(std::unique_ptr<Entity::Entity> entity);
            Entity::Entity* getEntity(const uint64& id);

			Entity::Entity* getPlayer() { return getEntity(player_id); }

			void setTile(unsigned int x, unsigned int y, Tile::Tile& tile);
            Tile::Tile* getTile(unsigned int x, unsigned int y);
            
            Entity::Entity* getEntityOnTile(unsigned int x, unsigned int y);

			void update(const Timestep& ts);
            void render(sf::RenderWindow& window);

        private:
            uint m_width;
            uint m_height;
            std::vector<Tile::Tile*> m_tiles;

			std::vector<std::unique_ptr<Entity::Entity>> m_entities;

			std::unique_ptr<Entity::System> m_renderSystem;
			std::vector<std::unique_ptr<Entity::System>> m_updateSystems;
		public:
			uint64 player_id;
	};
}
