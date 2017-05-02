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
		bool flipOnVelocity; // flipX based on +- velocity
		bool flipX, flipY;

		SpriteComponent(const sf::Sprite& sprite);
		SpriteComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override
		{
			return std::make_unique<SpriteComponent>(*this);
		}

		static const int ID = 7;
	};
}
