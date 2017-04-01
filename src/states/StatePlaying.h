#pragma once

#include <SFML/Graphics.hpp>

#include "StateBase.h"

#include "../entity/Entity.h"
#include "../level/TileMap.h"

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
			entity::Entity* m_entity;
            Level::TileMap m_tileMap;
    };
}
