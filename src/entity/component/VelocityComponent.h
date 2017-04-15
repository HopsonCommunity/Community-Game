#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

namespace Framework
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

            static ComponentType* getStaticType();
            virtual ComponentType* getType() const override;;
	};
}
