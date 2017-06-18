#include "StatePlaying.h"

#include "../../level/tile/TileDatabase.h"
#include "../../level/gen/WorldGenerator.h"

#include "../Application.h"
#include "../../Common.h"
#include "../../util/Random.h"
#include "../../util/Log.h"
#include "../../entity/EntityFactory.h"
#include "../../components/PhysicsComponent.h"
#include "../../components/LightComponent.h"

namespace State
{
	Playing* Playing::s_instance;
	Entity::EntityFactory* Playing::entityFactory;
	Item::ItemFactory* Playing::itemFactory;

	Playing::Playing(Application* app, sf::RenderWindow* window)
		: Base(app)
		, m_level(WORLD_SIZE, WORLD_SIZE)
	{
		s_instance = this;

		entityFactory = new Entity::EntityFactory();

		std::unique_ptr<Entity::Entity> player = entityFactory->createEntity("Player.json");
		LOG_INFO("Player ID: ", player.get()->getID());

		m_level.player = player.get();
		m_level.addEntity(std::move(player));

		m_level.player->getComponent<Components::PhysicsComponent>()->pos = { m_level.player_spawn.x * 32.0f, m_level.player_spawn.y * 32.0f };

		std::unique_ptr<Entity::Entity> lantern2 = entityFactory->createEntity("Lantern.json");
		lantern2->getComponent<Components::PhysicsComponent>()->pos = { m_level.player_spawn.x * 32.0f - 20, m_level.player_spawn.y * 32.0f - 50 };

		m_level.addEntity(std::move(lantern2));
		
		std::unique_ptr<Entity::Entity> zombie = entityFactory->createEntity("enemy/Zombie.json");
		zombie->getComponent<Components::PhysicsComponent>()->pos = { m_level.player_spawn.x * 32.0f, m_level.player_spawn.y * 32.0f };
		m_level.addEntity(std::move(zombie));
	}

	void Playing::onEvent(Events::Event& event)
	{
		//if (event.type == sf::Event::Resized)
		//	m_level.windowResize({ static_cast<float>(event.size.width), static_cast<float>(event.size.height) });
	}

	void Playing::update(const Timestep& ts)
	{
		m_level.update(ts);
	}

	void Playing::render(sf::RenderWindow& window)
	{
		m_level.render(window);
	}

	void Playing::tick()
	{
	}
	bool Playing::isTilePassable(byte layer, uint x, uint y)
	{
		Level::TileNode* tile = getLevel().getTiles().getTile(layer, x, y);
		return tile ? Level::TileDatabase::get().getTileData(byte(tile->id)).flags & int32(Level::TileFlags::PASSABLE) : true;
	}
}
