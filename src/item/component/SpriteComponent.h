#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "../../util/json.hpp"
#include "Component.h"
#include "Components.h"

namespace Item {
    class SpriteComponent : public Component {
    public:
        SpriteComponent();
        SpriteComponent(nlohmann::json json);


        sf::Sprite sprite;
        static const uint ID = ComponentID::Sprite;
    };
}
