#include "Level.h"

#include "gen/WorldGenerator.h"

#include "../util/Timestep.h"
#include "../app/Application.h"
#include "../entity/component/PhysicsComponent.h"

namespace Level
{
	Level::Level(uint width, uint height)
		: m_tiles(TileMap(width, height)), player(nullptr)
	{
		WGenerator::WorldGenerator m_worldGen(WORLD_SIZE, WORLD_SIZE, 2355);
		m_worldGen.generateMap();

		auto data = m_worldGen.getMap();
		TileMap::AddList addList;

		for (int x = 0; x < WORLD_SIZE; x++)
			for (int y = 0; y < WORLD_SIZE; y++)
			{
				auto n = data.tiles[x][y];
				if (n == 1)
					addList.push_back(std::make_tuple(x, y, byte(TileID::Dungeon_BrickFloor), 0 ));
				else if (n == 0)
					addList.push_back(std::make_tuple( x, y, byte(TileID::Dungeon_BrickWall), 0 ));
				else
					addList.push_back(std::make_tuple( x, y, byte(TileID::Void), 0));
			}

		m_tiles.addTiles(0, addList);

		player_spawn = Vec2i(data.playerPosition);

		m_renderSystem = std::move(std::make_unique<Entity::RenderSystem>());

		m_updateSystems.push_back(std::move(std::make_unique<Entity::LightingSystem>()));
		m_updateSystems.push_back(std::move(std::make_unique<Entity::PlayerInputSystem>()));
		m_updateSystems.push_back(std::move(std::make_unique<Entity::AISystem>()));
		m_updateSystems.push_back(std::move(std::make_unique<Entity::MoveSystem>()));
		m_updateSystems.push_back(std::move(std::make_unique<Entity::StatsSystem>()));
		m_updateSystems.push_back(std::move(std::make_unique<Entity::AnimatorSystem>()));

		m_view = sf::View(Vec2(0, 0), Vec2(static_cast<float>(Application::instance->getWindow().getSize().x), static_cast<float>(Application::instance->getWindow().getSize().y)));
	}

	void Level::addEntity(std::unique_ptr<Entity::Entity> entity)
	{
		m_entities.push_back(std::move(entity));
	}

	void Level::render(sf::RenderWindow& window)
	{
		window.setView(m_view);
		m_tiles.render(window);

		for (auto& entity : m_entities)
			m_renderSystem->update(Timestep(0), entity.get());
	}

	void Level::update(const Timestep& ts)
	{
		for (auto& entity : m_entities)
			for (auto& system : m_updateSystems)
				system->update(ts, entity.get());

		m_tiles.light();

		Entity::PhysicsComponent* c_pos = player->getComponent<Entity::PhysicsComponent>();

		Vec2 offset = (Vec2(Application::instance->mousePosition()) - Vec2(Application::instance->getWindow().getSize()) / 2.f) * .1f;
		m_view.setCenter(c_pos->pos.x + offset.x, c_pos->pos.y + offset.y);


		TileMap::AddList x3;
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				int x = int(c_pos->pos.x) / 32 + i;
				int y = int(c_pos->pos.y) / 32 + j;

				if (m_tiles.getTile(0, x, y)->id != TileID::Dungeon_BrickFloor)
					x3.push_back({x, y, byte(TileID::Dungeon_BrickFloor), 0 });
			}
		m_tiles.addTiles(0, x3);
		x3.clear();
	}

	void Level::windowResize(Vec2 size)
	{
		m_view.setSize(size.x, size.y);
	}

	void Level::removeEntity(Entity::Entity* entity)
	{
		for (uint i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i].get() == entity)
			{
				m_entities.erase(m_entities.begin() + i);
				break;
			}
		}
	}
}
