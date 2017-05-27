#pragma once

#include "../Common.h"

#include "tile/TileMap.h"
#include "../entity/Entity.h"
#include "../entity/system/System.h"
#include "../item/system/DrawingSystems.h"

#define WORLD_SIZE 100

namespace Level
{
	class Level
	{
	public:
		Level(uint width, uint height);

		void addEntity(std::unique_ptr<Entity::Entity> entity);
		void removeEntity(Entity::Entity* entity);

		void render(sf::RenderWindow& window);
		void update(const Timestep& ts);
		void windowResize(Vec2 size);

		TileMap& getTiles() { return m_tiles; }

	private:
		sf::View m_view;
		TileMap m_tiles;

		std::unique_ptr<Entity::System> m_renderSystem;

		std::vector<std::unique_ptr<Entity::Entity>> m_entities;
		std::vector<std::unique_ptr<Entity::System>> m_updateSystems;
	public:
		Entity::Entity* player;
		Vec2i player_spawn;
	};
}
