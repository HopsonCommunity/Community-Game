#include "StatePlaying.h"

#include "../Application.h"

namespace State
{
    SPlaying::SPlaying(Application* app)
    : SBase(app)
    , m_testFloat(0)
    , m_player()
    , m_debugMenu(app->getResources().fonts.get("SourceCodePro-Regular"))
    {
        m_debugMenu.addEntry("A", &m_testInt, 0.0f, 1.0f);
        m_debugMenu.addEntry("B", &m_testFloat, 0.0f, 1.0f);
        m_debugMenu.addEntry("C", &m_testBool);
    }

    void SPlaying::event(sf::Event& event)
    {
    }

    void SPlaying::input()
    {
		if (m_pApplication->inputPressed("PRINT_TEST"))
			std::cout << "Debug" << std::endl;

		m_player.input(m_pApplication);
			
        m_debugMenu.input();
    }

    void SPlaying::update(float dt)
    {
        m_player.update(dt);

        m_testFloat = dt;
        m_testInt = dt * 10000;
        m_testBool = m_testInt % 2 == 1 ? true : false;
    }

    void SPlaying::render(sf::RenderWindow& window)
    {
        m_player.render(window);
       // m_tileMap.draw(window);
        m_debugMenu.render();
    }
}
