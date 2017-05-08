#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "../../util/json.hpp"
#include "Component.h"

namespace Item {
    class SpriteComponent : public Component {
    public:
        SpriteComponent();
        SpriteComponent(nlohmann::json json);


        sf::Sprite sprite;
        static const int ID = 1;
    };
}
