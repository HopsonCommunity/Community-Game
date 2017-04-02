#include "StatePlaying.h"

#include "../Application.h"

namespace State
{
	SPlaying::SPlaying(Application* app)
	: SBase(app)
	, m_player()
	, m_tileMap({}, 5, 5)
	{
		// This is actually what -> does if you didnt know :)
		m_entity.getShape().setFillColor(sf::Color(0.2 * 255, 0.3 * 255, 0.8 * 255, 255));
	}

    void SPlaying::event(sf::Event& event)
    {
    }

    void SPlaying::input()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_player.velocity.x += 0.1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_player.velocity.x -= 0.1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			m_player.velocity.y -= 0.1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			m_player.velocity.y += 0.1;
    }

    void SPlaying::update(float dt)
    {
		m_player.getShape().move(m_player.velocity);

		m_player.update();

        ///@TODO Make velocity dampening scale with FPS/ dt
		m_player.velocity *= 0.98f;
    }

    void SPlaying::render(sf::RenderWindow& window)
    {
		m_player.render(window);
        m_tileMap.draw(window);
    }
}
