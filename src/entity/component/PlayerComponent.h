#pragma once

#include "Component.h"

#include "../../util/json.hpp"

namespace Entity
{
    class PlayerComponent : public Component
    {
    public:
        PlayerComponent();
        PlayerComponent(nlohmann::json json);

        static const int ID = 5;
    };
}
