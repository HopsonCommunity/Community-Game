#pragma once

#include "Component.h"

#include "../../util/json.hpp"

#include <SFML/Graphics.hpp>

namespace Entity
{
    class VelocityComponent : public Component
    {
    public:
        float speed;
        Vec2 velocity;
        bool moving;

        VelocityComponent(const Vec2& velocity = {});
        VelocityComponent(nlohmann::json json);

        // Move at an angle
        void move(float angle);

        // Move x/y direction
        void move(int xa, int ya);

        static const int ID = 9;
    };
}
