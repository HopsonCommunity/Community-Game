#pragma once

#include <SFML/Graphics.hpp>

#include "StateBase.h"

#include "../entity/Player.h"
#include "../level/Level.h"
#include "../level/Tile/TileMap.h"
#include "../debug/DebugMenu.h"
#include "../level/WorldGenerator/WorldGenerator.h"

class Application;

namespace State
{
    class SPlaying : public SBase
    {
        public:
            SPlaying(Application* app, sf::RenderWindow& window);

            void event(sf::Event& event) override;
            void input() override;
            void update(const Timestep& ts) override;
            void render(sf::RenderWindow& window) override;
        private:
            //Level::Tile::Map m_tileMap;
			sf::RenderWindow& m_window;
			sf::View m_camera;
			Framework::Player m_player;
			Level::Level m_level;
            Debug::DebugMenu m_debugMenu;
            float m_testFloat;
            int m_testInt;
            bool m_testBool;
            WGenerator::WorldGenerator m_worldGen;
    };
}
