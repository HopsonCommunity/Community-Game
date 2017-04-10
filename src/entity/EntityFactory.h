#pragma once

#include "../util/json.hpp"
#include "Entity.h"

namespace Entity {
    class EntityFactory {
    public:
        static std::unique_ptr<Framework::Entity> createEntity(std::string filePath);
        static uint m_lastID;
    };
}
