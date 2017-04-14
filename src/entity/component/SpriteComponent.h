#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Component.h"
#include "../animation/Animator.h"
#include "../../util/json.hpp"

namespace Framework
{
	class SpriteComponent : public Component
	{
	public:
		sf::Vector2f origin;
		sf::Sprite sprite;
		bool flipX, flipY;
	public:
		SpriteComponent(const sf::Sprite& sprite);
		SpriteComponent(nlohmann::json json);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
