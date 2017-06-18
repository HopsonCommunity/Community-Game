#include "Level.h"

#include "gen/WorldGenerator.h"

#include "../util/Timestep.h"
#include "../app/Application.h"
#include "../components/PhysicsComponent.h"

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
		m_updateSystems.push_back(std::move(std::make_unique<Entity::ScriptSystem>()));
		m_updateSystems.push_back(std::move(std::make_unique<Entity::MoveSystem>()));
		m_updateSystems.push_back(std::move(std::make_unique<Entity::StatsSystem>()));
		m_updateSystems.push_back(std::move(std::make_unique<Entity::AnimatorSystem>()));

		m_view = sf::View(Vec2(0, 0), Vec2(static_cast<float>(Application::get().getWindow().getSize().x), static_cast<float>(Application::get().getWindow().getSize().y)));
	}

	void Level::addEntity(std::unique_ptr<Entity::Entity> entity)
	{
		m_entities.push_back(std::move(entity));
	}

	void Level::render(sf::RenderWindow& window)
	{
		window.setView(m_view);

		m_tiles.render(window, IntRectangle(Vec2i((m_view.getCenter() - m_view.getSize()) / TILE_SIZE), Vec2i((m_view.getSize() * 2.f) / TILE_SIZE)));

		std::sort(m_entities.begin(), m_entities.end(),
			[](const std::unique_ptr<Entity::Entity>& lhs, const std::unique_ptr<Entity::Entity>& rhs) {
			Components::PhysicsComponent* c_lhs = lhs.get()->getComponent<Components::PhysicsComponent>();
			Components::PhysicsComponent* c_rhs = rhs.get()->getComponent<Components::PhysicsComponent>();
			return c_lhs->pos.y + c_lhs->sortOffset < c_rhs->pos.y + c_rhs->sortOffset;
		});

		m_tiles.presentBefore(window);

		for (auto& entity : m_entities)
			m_renderSystem->update(Timestep(0), entity.get());

		m_tiles.presentAfter(window);

		/*
			Show Zombie's path towards the player
		*/
#define AI_PATH 0
#if AI_PATH
		sf::RenderStates states;
		for (auto vec : m_visualPath)
		{
			auto rs = sf::RectangleShape({2, 2});
			rs.setPosition({static_cast<float>(vec.x) * TILE_SIZE + TILE_SIZE / 2 - 1.f, static_cast<float>(vec.y) * TILE_SIZE + TILE_SIZE / 2 - 1.f});
			rs.setFillColor({ 255, 0, 0, 255 });
			Application::get().getWindow().draw(rs, states);
		}
#endif
	
		m_tiles.renderLight(window);
	}

	void Level::update(const Timestep& ts)
	{
		for (auto& entity : m_entities)
			for (auto& system : m_updateSystems)
				system->update(ts, entity.get());

		m_tiles.light();

		Components::PhysicsComponent* c_pos = player->getComponent<Components::PhysicsComponent>();

		Vec2 offset = (Vec2(Application::get().getInputManager()->getMouse()) - Vec2(Application::get().getWindow().getSize()) / 2.f) * .1f;
		m_view.setCenter(c_pos->pos + offset);
	
		/*
			Remove tiles in 3x3 area around the player's position
		*/
#define REMOVE_TILES 0
#if REMOVE_TILES
		TileMap::AddList x3;
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				int x = int(c_pos->pos.x) / 32 + i;
				int y = int(c_pos->pos.y + 16) / 32 + j;

				if (m_tiles.getTile(0, x, y)->id != TileID::Dungeon_BrickFloor)
					x3.push_back({x, y, byte(TileID::Dungeon_BrickFloor), 0 });
			}
		m_tiles.addTiles(0, x3);
		x3.clear();
#endif
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
