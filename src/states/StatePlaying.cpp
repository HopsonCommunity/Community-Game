#include "StatePlaying.h"

#include "../Application.h"
#include "../level/Tile/Tile.h"
#include "../level/LevelRenderer.h"

namespace State
{
    SPlaying::SPlaying(Application* app, sf::RenderWindow& window)
    : SBase(app)
    , m_testFloat(0)
	, m_window(window)
	, m_camera()
    , m_player()
	, m_level(5, 5)
    , m_debugMenu(app->getResources().fonts.get("SourceCodePro-Regular"))
    {
        m_debugMenu.addEntry("A", &m_testInt, 0.0f, 1.0f);
        m_debugMenu.addEntry("B", &m_testFloat, 0.0f, 1.0f);
        m_debugMenu.addEntry("C", &m_testBool);

		m_camera = sf::View(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y));
		window.setView(m_camera);

		m_level.addEntity(&m_player);

		Level::Tile::Tile::loadTiles();

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

    }

    void SPlaying::event(sf::Event& event)
    {

    }

    void SPlaying::input()
    {
		if (m_pApplication->inputPressed("PRINT_TEST"))
			std::cout << "Debug" << std::endl;

        m_debugMenu.input();
    }

    void SPlaying::update(float dt)
    {
		m_level.update(dt);
		m_camera.setCenter(m_player.position);

        m_testFloat = dt;
        m_testInt = dt * 10000;
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
