#include "State_Playing.h"

namespace State
{
	SPlaying::SPlaying(Application* app)
		: SBase(app)
		, m_entity(new entity::Entity(100, 100))
	{
		// This is actually what -> does if you didnt know :)
		(*m_entity).getShape().setFillColor(sf::Color(0.2 * 255, 0.3 * 255, 0.8 * 255, 255));
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
    }

    void SPlaying::update(float dt)
    {
		m_entity->getShape().move(m_entity->velocity);

        ///@TODO Make velocity dampening scale with FPS/ dt
        m_entity->velocity *= 0.98f;
    }

    void SPlaying::render(sf::RenderWindow& window)
    {
		m_entity->render(window);
    }
}
