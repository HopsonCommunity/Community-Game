#pragma once

#include "Component.h"

#include "../../util/json.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace Entity
{
	class SpriteComponent : public Component
	{
    public:
		Vec2 origin;
		sf::Sprite sprite;
		bool flipX, flipY;

		SpriteComponent(const sf::Sprite& sprite);
		SpriteComponent(nlohmann::json json);

        static const int ID = 7;
	};
}
