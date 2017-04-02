#pragma once

#include <SFML/Graphics.hpp>

#include "StateBase.h"

#include "../entity/Player.h"
#include "../level/Tile/TileMap.h"
#include "../debug/DebugMenu.h"

class Application;

namespace State
{
    class SPlaying : public SBase
    {
        public:
            SPlaying(Application* app);

            void event(sf::Event& event) override;
            void input() override;
            void update(float dt) override;
            void render(sf::RenderWindow& window) override;
        private:
			Framework::Player m_player;
            Level::Tile::Map m_tileMap;
            Debug::DebugMenu m_debugMenu;
            float m_testFloat;
            int m_testInt;
            bool m_testBool;
    };
}
