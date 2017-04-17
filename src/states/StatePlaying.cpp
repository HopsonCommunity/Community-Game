#include "StatePlaying.h"

#include "../Application.h"
#include "../level/Tile/Tile.h"
#include "../level/LevelRenderer.h"
#include "../entity/component/Components.h"
#include "../entity/EntityFactory.h"

using namespace std::placeholders;

namespace State
{

	 SPlaying* SPlaying::instance = nullptr;

    namespace
    {
        constexpr int WORLD_SIZE = 100;

        float m_testFloat;
        int m_testInt;
        bool m_testBool;
    }



	SPlaying::SPlaying(Application* app, sf::RenderWindow& window)
    :   SBase           (app)
    ,   m_level         (WORLD_SIZE, WORLD_SIZE)
    ,   m_window        (window)
    ,   m_debugMenu     (app->getResources().fonts.get("SourceCodePro-Regular"))
    ,   m_worldGen      (WORLD_SIZE, WORLD_SIZE, 2355)
    ,   m_ui            (&window)
    ,   m_button        (UI::Label(sf::Text("Test Button", app->getResources().fonts.get("SourceCodePro-Regular"), 18)), sf::Rect<int>(10, 10, 150, 50), std::bind(&SPlaying::buttonCallback, this))
    ,   m_slider        (UI::Label(sf::Text("Test Slider", app->getResources().fonts.get("SourceCodePro-Regular"), 18)), sf::Rect<int>(10, 70, 150, 50), std::bind(&SPlaying::sliderCallback, this, _1))
	,   m_entityFactory ()
    {
		instance = this;

        m_debugMenu.addEntry("A", &m_testInt, 0, 1);
        m_debugMenu.addEntry("B", &m_testFloat, 0, 1);
        m_debugMenu.addEntry("C", &m_testBool);

        m_ui.addComponent(m_button);
		m_ui.addComponent(m_slider);

		m_camera = sf::View(Vec2(0, 0), Vec2(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
		window.setView(m_camera);

		std::unique_ptr<Entity::Entity> player = m_entityFactory.createEntity("Player");

		m_level.player_id = player->getID();
		std::cout << "Player ID: " << m_level.player_id << std::endl;

		m_level.addEntity(std::move(player));

		Level::Tile::Tile::loadTiles();

        m_worldGen.generateMap();

        auto data = m_worldGen.getMap();

        for (int x = 0; x < WORLD_SIZE; x++)
            for (int y = 0; y < WORLD_SIZE; y++)
            {
                auto n = data.tiles.at(x).at(y);
                if (n == 1)
                    m_level.setTile(x, y, *Level::Tile::Tile::fLightStone);
                else
                    m_level.setTile(x, y, *Level::Tile::Tile::stoneWall);
            }

		m_level.getEntity(m_level.player_id)->getComponent<Entity::PositionComponent>()->position = Vec2(static_cast<float>(data.playerPosition.x * 32), static_cast<float>(data.playerPosition.y * 32));

		std::unique_ptr<Entity::Entity> zombie = m_entityFactory.createHostileEntity();
		zombie->getComponent<Entity::PositionComponent>()->position = Vec2(static_cast<float>(data.playerPosition.x * 32 + 210), static_cast<float>(data.playerPosition.y * 32 + 210));

		m_level.addEntity(std::move(zombie));
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
		int offsetX = static_cast<int>((mouseX - halfWidth) * 0.1f);
		int offsetY = static_cast<int>((mouseY - halfHeight) * 0.1f);

		Entity::PositionComponent* c_pos = m_level.getEntity(m_level.player_id)->getComponent<Entity::PositionComponent>();
		m_camera.setCenter(c_pos->position.x + offsetX, c_pos->position.y+0.01f +offsetY);

        m_testFloat = ts.asSeconds();
        m_testInt = static_cast<int>(ts.asMillis());
        m_testBool = m_testInt % 2 == 1 ? true : false;

		Input::Input input = Application::instance->getInputManager();
        m_ui.update(input);
    }

    void SPlaying::render(sf::RenderWindow& window)
    {
		window.setView(m_camera);
		Level::LevelRenderer::setRenderWindow(&window);
		m_level.render(window);
        m_debugMenu.render();
        m_ui.render();
    }

	int i = 0;
	void SPlaying::tick()
	{
		if (i == 0)
		{
			std::unique_ptr<Entity::Entity> e = m_entityFactory.createEntity("Projectile");
			e->getComponent<Entity::PositionComponent>()->position = m_level.getPlayer()->getComponent<Entity::PositionComponent>()->position;
			e->getComponent<Entity::VelocityComponent>()->velocity.x = 10;
			m_level.addEntity(std::move(e));
		}
		i++;
	}
}
