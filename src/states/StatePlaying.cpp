#include "StatePlaying.h"

namespace State
{
	SPlaying::SPlaying(Application* app)
	: SBase(app)
	, m_entity(new entity::Entity(100, 100))
    , testFloat(0)
	, m_tileMap({}, 5, 5)
    , m_debugMenu(app->getResources().fonts.get("SourceCodePro-Regular"))
	{
		// This is actually what -> does if you didnt know :)
		(*m_entity).getShape().setFillColor(sf::Color(0.2 * 255, 0.3 * 255, 0.8 * 255, 255));

        m_debugMenu.addEntry("Test Float", &testFloat, 0.0f, 1.0f);
	}

    void SPlaying::event(sf::Event& event)
    {
    }

    void SPlaying::input()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_entity->velocity.x += 0.1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            m_entity->velocity.x -= 0.1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            m_entity->velocity.y -= 0.1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            m_entity->velocity.y += 0.1;

        m_debugMenu.input();
    }

    void SPlaying::update(float dt)
    {
		m_entity->getShape().move(m_entity->velocity);

        ///@TODO Make velocity dampening scale with FPS/ dt
        m_entity->velocity *= 0.98f;

        testFloat = dt;
    }

    void SPlaying::render(sf::RenderWindow& window)
    {
		m_entity->render(window);
        m_tileMap.draw(window);
        m_debugMenu.render();
    }
}
