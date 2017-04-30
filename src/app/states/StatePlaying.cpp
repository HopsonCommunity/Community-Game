#include "StatePlaying.h"

#include "../../level/gen/WorldGenerator.h"

#include "../Application.h"
#include "../../Common.h"
#include "../../maths/Random.h"
#include "../../util/Log.h"
#include "../../entity/EntityFactory.h"

namespace State
{
	Playing::Playing(Application* app, sf::RenderWindow* window)
		: Base(app)
		, m_level(WORLD_SIZE, WORLD_SIZE)
	{
		Entity::EntityFactory factory;

		std::unique_ptr<Entity::Entity> player = factory.createEntity("Player");
		LOG_INFO("Player ID: ", player.get()->getID());

		m_level.player = player.get();
		m_level.addEntity(std::move(player));
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