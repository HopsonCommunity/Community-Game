#include "StatePlaying.h"

#include "../Application.h"

namespace State
{
    SPlaying::SPlaying(Application* app)
    : SBase(app)
    , m_testFloat(0)
    , m_player()
    , m_tileMap({}, 5, 5)
    , m_debugMenu(app->getResources().fonts.get("SourceCodePro-Regular"))
    {
        m_debugMenu.addEntry("A", &m_testInt, 0.0f, 1.0f);
        m_debugMenu.addEntry("B", &m_testFloat, 0.0f, 1.0f);
        m_debugMenu.addEntry("C", &m_testBool);
        m_player.getShape().setFillColor(sf::Color(0.2 * 255, 0.3 * 255, 0.8 * 255, 255));
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

        m_debugMenu.input();
    }

    void SPlaying::update(float dt)
    {
        m_player.getShape().move(m_player.velocity);

        m_player.update();

        m_testFloat = dt;
        m_testInt = dt * 10000;
        m_testBool = m_testInt % 2 == 1 ? true : false;
    }

    void SPlaying::render(sf::RenderWindow& window)
    {
        m_player.render(window);
        m_tileMap.draw(window);
        m_debugMenu.render();
    }
}
