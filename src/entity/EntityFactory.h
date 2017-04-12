#pragma once

#include "../util/json.hpp"
#include "Entity.h"

namespace Entity {
    class EntityFactory {
    public:
        static std::unique_ptr<Framework::Entity> createEntity(std::string filePath);

        //Temporary functions to test ECS till JSON is fully implemented
        static std::unique_ptr<Framework::Entity> createPlayer();
        static std::unique_ptr<Framework::Entity> createZombie(const sf::Vector2f& position);

        static uint m_lastID;
    };
}
