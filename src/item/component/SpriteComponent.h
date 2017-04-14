#pragma once

#include "../../util/json.hpp"
#include "Component.h"

namespace Item {
    class SpriteComponent : Component {
    public:
        SpriteComponent(nlohmann::json json);

        static ComponentType* getStaticType();
        virtual ComponentType* getType() const override;

        sf::Sprite sprite;
    };
}
