#include "StatePlaying.h"

#include "../../level/gen/WorldGenerator.h"

#include "../Application.h"
#include "../../Common.h"
#include "../../maths/Random.h"
#include "../../util/Log.h"
#include "../../entity/EntityFactory.h"
#include "../../entity/component/PositionComponent.h"

namespace State
{
	Playing* Playing::instance;

	Playing::Playing(Application* app, sf::RenderWindow* window)
		: Base(app)
		, m_level(WORLD_SIZE, WORLD_SIZE)
	{
		instance = this;

		Entity::EntityFactory factory;

		std::unique_ptr<Entity::Entity> player = factory.createEntity("Player");
		LOG_INFO("Player ID: ", player.get()->getID());

		m_level.player = player.get();
		m_level.addEntity(std::move(player));

		m_level.player->getComponent<Entity::PositionComponent>()->position = { m_level.player_spawn.x * 32.0f, m_level.player_spawn.x * 32.0f };

		std::unique_ptr<Entity::Entity> zombie = factory.createEntity("enemy/Zombie");
		zombie->getComponent<Entity::PositionComponent>()->position = { m_level.player_spawn.x * 32.0f + 210, m_level.player_spawn.x * 32.0f + 210 };

		m_level.addEntity(std::move(zombie));
	}

	void Playing::event(sf::Event& event)
	{
		if (event.type == sf::Event::Resized)
			m_level.windowResize({ static_cast<float>(event.size.width), static_cast<float>(event.size.height) });
	}

	void Playing::input()
	{
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
}