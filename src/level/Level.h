#pragma once

#include "Tile/Tile.h"
#include <iostream>
#include "../util/Timestep.h"

#include "../entity/system/System.h"
#include "../item/system/DrawingSystems.h"

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

			Framework::Entity* getPlayer() { return getEntity(player_id); }

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
            std::vector<std::shared_ptr<Item::Item>> m_items;

			std::unique_ptr<Framework::System> m_renderSystem;
            std::unique_ptr<Item::SpriteDrawingSystem> m_itemRenderSystem;
			std::vector<std::unique_ptr<Framework::System>> m_updateSystems;
            std::vector<std::unique_ptr<Item::System>> m_itemUpdateSystems;
		public:
			uint64 player_id;
	};
}
