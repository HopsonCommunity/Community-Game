#include "StatePlaying.h"

#include "../Application.h"
#include "../level/Tile/Tile.h"
#include "../level/LevelRenderer.h"

namespace State
{
    namespace Test
    {
        constexpr int WORLD_SIZE = 50;
    }

    SPlaying::SPlaying(Application* app, sf::RenderWindow& window)
    :   SBase(app)
    ,   m_testFloat(0)
	,   m_window(window)
	,   m_camera()
    ,   m_player()
	,   m_level(Test::WORLD_SIZE, Test::WORLD_SIZE)
    ,   m_debugMenu(app->getResources().fonts.get("SourceCodePro-Regular"))
    ,   m_worldGen(Test::WORLD_SIZE, Test::WORLD_SIZE, 23535)
    {
        m_debugMenu.addEntry("A", &m_testInt, 0, 1);
        m_debugMenu.addEntry("B", &m_testFloat, 0, 1);
        m_debugMenu.addEntry("C", &m_testBool);

		m_camera = sf::View(sf::Vector2f(0, 0), sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
		window.setView(m_camera);

		m_level.addEntity(&m_player);

		Level::Tile::Tile::loadTiles();

        m_worldGen.generate();

        auto data = m_worldGen.debug();

        for (int x = 0; x < Test::WORLD_SIZE; x++)
        {
            for (int y = 0; y < Test::WORLD_SIZE; y++)
            {
                auto n = data.at(x).at(y);
                if (n == 0)
                {
                    m_level.setTile(x, y, *Level::Tile::Tile::fLightStone);
                }
                else
                {
                    m_level.setTile(x, y, *Level::Tile::Tile::stoneWall);

                }
            }
        }

        m_player.sprite.setPosition(500,500);
/*
		m_level.setTile(0, 0, *Level::Tile::Tile::fLightStone);
		m_level.setTile(2, 0, *Level::Tile::Tile::fLightStone);
		m_level.setTile(3, 0, *Level::Tile::Tile::fDarkStone);
		m_level.setTile(4, 0, *Level::Tile::Tile::fLightStone);

		m_level.setTile(0, 1, *Level::Tile::Tile::fDarkStone);
		m_level.setTile(2, 1, *Level::Tile::Tile::fDarkStone);
		m_level.setTile(3, 1, *Level::Tile::Tile::fDarkStone);
		m_level.setTile(4, 1, *Level::Tile::Tile::fDarkStone);

		m_level.setTile(0, 2, *Level::Tile::Tile::fDarkStone);
		m_level.setTile(4, 2, *Level::Tile::Tile::fDarkStone);

		m_level.setTile(0, 3, *Level::Tile::Tile::fDarkStone);
		m_level.setTile(1, 3, *Level::Tile::Tile::stoneWall);
		m_level.setTile(2, 3, *Level::Tile::Tile::stoneWall);
		m_level.setTile(3, 3, *Level::Tile::Tile::stoneWall);
		m_level.setTile(4, 3, *Level::Tile::Tile::fDarkStone);

		m_level.setTile(0, 4, *Level::Tile::Tile::fDarkStone);
		m_level.setTile(1, 4, *Level::Tile::Tile::fDarkStone);
		m_level.setTile(2, 4, *Level::Tile::Tile::fDarkStone);
		m_level.setTile(3, 4, *Level::Tile::Tile::fDarkStone);
		m_level.setTile(4, 4, *Level::Tile::Tile::fDarkStone);
*/
    }

    void SPlaying::event(sf::Event& event)
    {
		if (event.type == sf::Event::EventType::Resized)
		{
			m_camera.setSize(static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y));
		}
    }

    void SPlaying::input()
    {
		if (m_pApplication->inputPressed("PRINT_TEST"))
			std::cout << "Debug" << std::endl;

        m_debugMenu.input();
    }

    void SPlaying::update(const Timestep& ts)
    {
		m_level.update(ts);

		int mouseX = Application::instance->mousePosition().x;
		int mouseY = Application::instance->mousePosition().y;
		int halfWidth = Application::instance->getWindow().getSize().x / 2;
		int halfHeight = Application::instance->getWindow().getSize().y / 2;
		float offsetX = (mouseX - halfWidth) * 0.1f;
		float offsetY = (mouseY - halfHeight) * 0.1f;
		m_camera.setCenter(m_player.position.x + offsetX, m_player.position.y + offsetY);

        m_testFloat = ts.asSeconds();
        m_testInt = static_cast<int>(ts.asMillis());
        m_testBool = m_testInt % 2 == 1 ? true : false;
    }

    void SPlaying::render(sf::RenderWindow& window)
    {
		window.setView(m_camera);
		Level::LevelRenderer::setRenderWindow(&window);
		m_level.render(window);
        //m_tileMap.draw(window);
        m_debugMenu.render();
    }
}
