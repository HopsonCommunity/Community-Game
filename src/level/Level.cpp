#include "Level.h"

#include "gen/WorldGenerator.h"

#include "../util/Timestep.h"
#include "../app/Application.h"
#include "../entity/component/PositionComponent.h"

namespace Level
{
	Level::Level(uint width, uint height)
		: m_tiles(TileMap(width, height))
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
					addList.push_back({ x, y, (byte)TileID::Dungeon_BrickFloor, 0 });
				else
					addList.push_back({ x, y, (byte)TileID::Dungeon_BrickWall, 0 });
			}

		m_tiles.addTiles(0, addList);

		player_spawn = Vec2i(data.playerPosition);

		m_renderSystem = std::make_unique<Entity::RenderSystem>();

		m_updateSystems.push_back(std::make_unique<Entity::MoveSystem>());
		m_updateSystems.push_back(std::make_unique<Entity::StatsSystem>());
		m_updateSystems.push_back(std::make_unique<Entity::AISystem>());
		m_updateSystems.push_back(std::make_unique<Entity::PlayerInputSystem>());
		m_updateSystems.push_back(std::make_unique<Entity::AnimatorSystem>());

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

		int mouseX = Application::instance->mousePosition().x;
		int mouseY = Application::instance->mousePosition().y;
		int halfWidth = Application::instance->getWindow().getSize().x / 2;
		int halfHeight = Application::instance->getWindow().getSize().y / 2;
		int offsetX = static_cast<int>((mouseX - halfWidth) * 0.1f);
		int offsetY = static_cast<int>((mouseY - halfHeight) * 0.1f);

		Entity::PositionComponent* c_pos = player->getComponent<Entity::PositionComponent>();
		m_view.setCenter(c_pos->position.x + offsetX, c_pos->position.y + 0.01 + offsetY);
	}

	void Level::windowResize(Vec2 size)
	{
		m_view.setSize(size.x, size.y);
	}
}