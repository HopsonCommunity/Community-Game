#include "StatePlaying.h"

#include "../../level/gen/WorldGenerator.h"

#include "../Application.h"
#include "../../Common.h"
#include "../../maths/Random.h"
#include "../../util/Log.h"

#define WORLD_SIZE 100

namespace State
{
	Playing::Playing(Application* app, sf::RenderWindow* window)
		: Base(app)
		, m_level(new Level::TileMap(WORLD_SIZE, WORLD_SIZE))
	{
		WGenerator::WorldGenerator m_worldGen(WORLD_SIZE, WORLD_SIZE, 2355);
		m_worldGen.generateMap();

		auto data = m_worldGen.getMap();

		Level::TileMap::AddList addList;

		for (int x = 0; x < WORLD_SIZE; x++)
			for (int y = 0; y < WORLD_SIZE; y++)
			{
				auto n = data.tiles[x][y];
				if (n == (byte)Level::TileID::Cobblestone)
					addList.push_back({x, y, (byte)Level::TileID::Cobblestone, 0});
			}

		m_level->addTiles(0, addList);

		//std::unique_ptr<Entity::Entity> player = Entity::EntityFactory::get().createEntity("Player");
		//LOG_INFO("Player ID: ", player.get()->getID());

		// m_level.player = player.get();
		// m_level.addEntity(std::move(player));
	}

	Playing::~Playing()
	{
		delete m_level;
	}

	void Playing::event(sf::Event & event)
	{
	}

	void Playing::input()
	{
	}

	void Playing::update(const Timestep& ts)
	{
	}

	void Playing::render(sf::RenderWindow& window)
	{
		m_level->draw(window);
	}

	void Playing::tick()
	{
	}
}