#pragma once

#include <SFML/Graphics.hpp>

#include "StateBase.h"

#include "../entity/Player.h"
#include "../level/Tile/TileMap.h"

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
    };
}
