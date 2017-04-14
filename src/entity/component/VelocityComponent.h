#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

#include "../../util/json.hpp"
#include "../../util/Types.h"
#include "../../maths/Maths.h"

namespace Framework
{
	class VelocityComponent : public Component
	{
        public:
            float speed;
            vec2 velocity;
            bool moving;

            VelocityComponent(const vec2& velocity = {});
            VelocityComponent(nlohmann::json json);

            // Move at an angle
            void move(float angle);

            // Move x/y direction
            void move(int xa, int ya);

            static ComponentType* getStaticType();
            virtual ComponentType* getType() const override;;
	};
}
