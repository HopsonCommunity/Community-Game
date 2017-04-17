#pragma once

#include "Component.h"

#include "../../util/json.hpp"

namespace Entity
{
    // Marks the entitey as hostile
    class HostileComponent : public Component
    {
    public:
        HostileComponent();
        HostileComponent(nlohmann::json json);

        static const int ID = 10;
    };
}